#include"pch.h"
#include"public.h"
#include"connection.h"
#include<iostream>
using namespace std;

connection::connection() {
	//��ʼ��һ������
	_conn = mysql_init(nullptr);
}
connection::~connection() {
	//��ʼ��һ������
	if (_conn != nullptr) {
		mysql_close(_conn);
	}
}

bool connection::connect(string ip,unsigned short port,string username,string password,string dbname){
	//������mysql����������ʵ����
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;

}

//�����ݿ���и��²�������update,delete,grant��
bool connection::update(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG("����ʧ��" + sql);
		//�������ʧ�ܵ�ԭ��
		cout << mysql_error(_conn) << endl;
		return false;
	}
	return true;
}

//�����ݿ���в�ѯ����
MYSQL_RES* connection::query(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG("����ʧ��" + sql);
		//�������ʧ�ܵ�ԭ��
		cout << mysql_error(_conn) << endl;
		return nullptr;
	}
	return mysql_use_result(_conn);
}

