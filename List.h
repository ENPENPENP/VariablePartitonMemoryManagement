#pragma once
using namespace std;

//������������
const int maxProcessNum = 10;
//�������ڴ棨KB��
const int maxMemory_KB = 10240;
//������Ƭ��С����
const int minPartitonSize = 50;

/*
���������������
*/
class List
{
public:
	List();
	virtual ~List();

	//�������
	virtual void ListFind() {}

	//�������
	virtual void showList() = 0;
};
