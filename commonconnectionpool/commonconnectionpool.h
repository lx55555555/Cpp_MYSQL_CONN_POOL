#include<string>
#include<queue>
#include<memory>
#include<mutex>
#include<functional>
#include<thread>
#include<atomic>
#include<condition_variable>
#include<iostream>
#include"connection.h"
using namespace std;

//单例模式设计线程池
class connectionpool {
private:
	connectionpool();
	~connectionpool();
	bool loadconfigfile();
	void produceconnectiontask();
	void scannerconnectiontask();
	string _ip, _username, _password, _dbname;
	unsigned short _port;
	int _initsize, _maxsize, _maxidletime, _connectiontimeout;
	queue<connection*> _connectionque;
	mutex _queuemutex;
	atomic_int _connectioncnt;
	condition_variable cv;
public:
	shared_ptr<connection> getconnection();
	static connectionpool* getconnectionpool();
};