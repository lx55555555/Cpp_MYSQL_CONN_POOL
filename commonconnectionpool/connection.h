#pragma once
#include<mysql.h>
#include<ctime>
#include<string>
using namespace std;
class connection {
private:
	//��mysql��������һ������
	MYSQL* _conn;
	//���ӵ�ʱ��
	clock_t _alivetime;
public:
	//���캯��
	connection();
	//��������
	~connection();
	//�������ݿ⺯��
	bool connect(string ip, unsigned short port, string username, string password, string dbname);
	//�����ݿ���и��²���
	bool update(string sql);
	//�����ݿ���в�ѯ����
	MYSQL_RES* query(string sql);
	//�����������ݿ�ʱ��
	void refreshalivetime() {
		_alivetime=clock();
	}
	//����������ݿ�ʱ��
	clock_t getalivetime()const {
		return clock() - _alivetime;
	}
};

