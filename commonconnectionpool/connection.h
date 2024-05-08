#pragma once
#include<mysql.h>
#include<ctime>
#include<string>
using namespace std;
class connection {
private:
	//与mysql服务器的一个连接
	MYSQL* _conn;
	//连接的时长
	clock_t _alivetime;
public:
	//构造函数
	connection();
	//析构函数
	~connection();
	//连接数据库函数
	bool connect(string ip, unsigned short port, string username, string password, string dbname);
	//对数据库进行更新操作
	bool update(string sql);
	//对数据库进行查询操作
	MYSQL_RES* query(string sql);
	//更新连接数据库时长
	void refreshalivetime() {
		_alivetime=clock();
	}
	//获得连接数据库时长
	clock_t getalivetime()const {
		return clock() - _alivetime;
	}
};

