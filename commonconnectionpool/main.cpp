#include "pch.h"
#include <iostream>
#include "connection.h"
#include"commonconnectionpool.h"
using namespace std;

int main(){
	//普通版
	/*connection conn;
	string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
	conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
	conn.update(sql);*/


	//无连接池 单线程
	/*clock_t begin = clock();
	for (int i = 0; i < 1000; i++) {
		connection conn;
		string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
		conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
		conn.update(sql);
	}
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;*/


	//连接池 单线程
	/*clock_t begin = clock();
	connectionpool* cp = connectionpool::getconnectionpool();
	for (int i = 0; i < 1000; i++) {
		shared_ptr<connection>sp = cp->getconnection();
		char sql[1024] = { 0 };
		sprintf(sql, " insert into user(id, name, age, sex) values(%d, '%s', %d, '%s')", 19, "evan", 18, "male");
		sp->update(sql);
	}
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl; */


	//连接池 多线程
	clock_t begin = clock();
	thread t1([]() {
		connectionpool* cp = connectionpool::getconnectionpool();
		for (int i = 0; i < 250; i++) {			
			char sql[1024] = { 0 };
			sprintf(sql, " insert into user(id, name, age, sex) values(%d, '%s', %d, '%s')", 19, "evan", 18, "male");
			shared_ptr<connection>sp = cp->getconnection();
			sp->update(sql);
		}
		});
	thread t2([]() {
		connectionpool* cp = connectionpool::getconnectionpool();
		for (int i = 0; i < 250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, " insert into user(id, name, age, sex) values(%d, '%s', %d, '%s')", 19, "evan", 18, "male");
			shared_ptr<connection>sp = cp->getconnection();
			sp->update(sql);
		}
		});
	thread t3([]() {
		connectionpool* cp = connectionpool::getconnectionpool();
		for (int i = 0; i < 250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, " insert into user(id, name, age, sex) values(%d, '%s', %d, '%s')", 19, "evan", 18, "male");
			shared_ptr<connection>sp = cp->getconnection();
			sp->update(sql);
		}
		});
	thread t4([]() {
		connectionpool* cp = connectionpool::getconnectionpool();
		for (int i = 0; i < 250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, " insert into user(id, name, age, sex) values(%d, '%s', %d, '%s')", 19, "evan", 18, "male");
			shared_ptr<connection>sp = cp->getconnection();
			sp->update(sql);
		}
		});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;


	//无连接池 多线程
	/*connection conn;
	conn.connect("10.117.50.241, "root", "evan", "chat");
	clock_t begin = clock();
	thread t1([]() {
		for (int i = 0; i < 250; i++) {
			connection conn;
			string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
			conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
			conn.update(sql); 
		}
		});
	thread t2([]() {
		for (int i = 0; i < 250; i++) {
			connection conn;
			string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
			conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
			conn.update(sql);
		}
		});
	thread t3([]() {
		for (int i = 0; i < 250; i++) {
			connection conn;
			string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
			conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
			conn.update(sql);
		}
		});
	thread t4([]() {
		for (int i = 0; i < 250; i++) {
			connection conn;
			string sql = "insert into user(id,name,age,sex) values(19, 'chenxueli', 20, 'female')";
			conn.connect("10.117.50.241", 3306, "root", "evan", "chat");
			conn.update(sql);
		}
		});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;*/
	return 0;
}
