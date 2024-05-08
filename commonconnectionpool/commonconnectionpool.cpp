#include "pch.h"
#include "public.h"
#include"commonconnectionpool.h"
#include<iostream>
#include<fstream>
using namespace std;


connectionpool::connectionpool() {
	if (!loadconfigfile()) {
		return;
	}
	for (int i = 0; i < _initsize; i++) {
		connection* p = new connection();
		p->connect(_ip, _port, _username, _password, _dbname);
		p->refreshalivetime();
		_connectionque.push(p);
		_connectioncnt++;
	}
	thread produce(bind(&connectionpool::produceconnectiontask, this));
	produce.detach();
	thread scanner(bind(&connectionpool::scannerconnectiontask, this));
	scanner.detach();
}
bool connectionpool::loadconfigfile() {
	FILE* f = fopen("mysql.ini", "r");
	if (f == nullptr) {
		LOG("error in loading configfile");
		return false;
	}
	while (!feof(f)) {
		char line[1024] = { 0 };
		fgets(line, 1024, f);
		string str = line;
		int idx = str.find('=', 0);
		if (idx == -1) {
			continue;
		}
		int endidx= str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx+1, endidx-idx-1);
		if (key == "ip") {
			_ip = value;
		}
		else if (key == "port") {
			_port = atoi(value.c_str());
		}
		else if (key == "username") {
			_username = value;
		}
		else if (key == "dbname") {
			_dbname = value;
		}
		else if (key == "password") {
			_password = value;
		}
		else if (key == "initsize") {
			_initsize = atoi(value.c_str());
		}
		else if (key == "maxsize") {
			_maxsize = atoi(value.c_str());
		}
		else if (key == "maxidletime") {
			_maxidletime = atoi(value.c_str());
		}
		else if (key == "connectiontimeout") {
			_connectiontimeout = atoi(value.c_str());
		}
	}
	return true;
}
connectionpool* connectionpool::getconnectionpool() {
	static connectionpool pool;
	return &pool;
}
void connectionpool::produceconnectiontask() {
	for (;;) {
		unique_lock<mutex> lock(_queuemutex);
		while (!_connectionque.empty()) {
			cv.wait(lock);
		}
		if (_connectioncnt < _initsize) {
			connection* p = new connection();
			p->connect(_ip, _port, _username, _password, _dbname);
			p->refreshalivetime();
			_connectionque.push(p);
			_connectioncnt++;
		}
		cv.notify_all();
	}
}
shared_ptr<connection>connectionpool::getconnection() {
	unique_lock<mutex>lock(_queuemutex);
	while (_connectionque.empty()) {
		if (cv_status::timeout == cv.wait_for(lock, chrono::microseconds(_connectiontimeout))) {
			if (_connectionque.empty()) {
				LOG("等待超时，连接失败");
				return nullptr;
			}
		}
	}
	shared_ptr<connection> sp(_connectionque.front(),
		[&](connection*p) {
			unique_lock<mutex>lock(_queuemutex);
			p->refreshalivetime();
			_connectionque.push(p);

		});
	_connectionque.pop();
	cv.notify_all();
	return sp;
}
void connectionpool::scannerconnectiontask() {
	for (;;) {
		this_thread::sleep_for(chrono::seconds(_maxidletime));
		unique_lock<mutex>lock(_queuemutex);
		while (_connectioncnt > _initsize) {
			connection* p = _connectionque.front();
			if (p->getalivetime() >= (_maxidletime * 1000)) {
				_connectionque.pop();
				_connectioncnt--;
				delete p;
			}
			else {
				break;
			}
		}
	}
}