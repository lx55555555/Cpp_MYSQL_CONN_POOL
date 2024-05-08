#include"pch.h"
#include"public.h"
#include"connection.h"
#include<iostream>
using namespace std;

connection::connection() {
	//初始化一个连接
	_conn = mysql_init(nullptr);
}
connection::~connection() {
	//初始化一个连接
	if (_conn != nullptr) {
		mysql_close(_conn);
	}
}

bool connection::connect(string ip,unsigned short port,string username,string password,string dbname){
	//建立与mysql服务器的真实连接
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;

}

//对数据库进行更新操作，如update,delete,grant等
bool connection::update(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG("更新失败" + sql);
		//输出更新失败的原因
		cout << mysql_error(_conn) << endl;
		return false;
	}
	return true;
}

//对数据库进行查询操作
MYSQL_RES* connection::query(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG("更新失败" + sql);
		//输出更新失败的原因
		cout << mysql_error(_conn) << endl;
		return nullptr;
	}
	return mysql_use_result(_conn);
}

