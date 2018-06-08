#pragma once
#include "List.h"
using namespace std;

/*
��ʾ���̵Ľṹ��
*/
struct processList {
	//�������к�
	int proID;
	//�����ڴ�
	int needMemo;
	//��ʼ��ַ
	int startAddr;
	//״̬��־��0��ʾ�ȴ���1��ʾ������
	int State;
	//ָ����һ�����̵�ָ��
	processList *next;
	//�����ʼ��
	processList() {
		proID = 0;
		needMemo = 0;
		startAddr = 0;
		State = 0;
		next = NULL;
	}
	processList(int pid, int nm) :
		proID(pid), needMemo(nm), startAddr(NULL), next(NULL) {
		State = 0;
	};
};

/*
���������
*/
class ProcessList :
	public List
{
public:
	ProcessList();
	virtual ~ProcessList();

	//���������ʼ��
	void processListInit();

	//�������
	void showList();

	//ɾ������
	void deleteProcess(processList *);

	//���ҷ�������ȡ������Ϣ
	processList * ListFind(int);

	//�����½���
	void processInsert(int, int);

	//�ȴ�������
	static  int  PROCESS_LIST_LENGTH;

	//��������ͷָ��
	processList *head;
};
