#pragma once
#include"ProcessList.h"
#include"FreePartition.h"
#include"AllocPartition.h"
using namespace std;

/*
�������ղ�����
*/
class ListOperation :
	public ProcessList, FreePartition, AllocPartition
{
public:
	ListOperation();
	~ListOperation();

	//������з���
	void giveFreePartition(processList *);

	//��ʼ����
	void startProcess(int);

	//�����������ѷ����������
	void moveProcessToAllocPartition(processList *);

	//���ո��ͷŵķ���
	void partitionRecyle(allocPartition *);

	//��������
	void endProcess(int);

	//�Ƿ��Զ���ʼ�½���
	void autoStartNewProcess();

	//�˵�
	void menu();

	//��ҳ
	int Index();

	//����ѡ��op
	int opInput();

	//����pid
	int pidInput();

	//���������С
	int sizeInput();

	//����Y/N����
	char operationInput();

	//��ʼ�½���
	int case1();

	//ɾ������
	int case2();

	//�鿴�����б�
	int case3();

	//�鿴���з����б�
	int case4();

	//�鿴�ѷ�������б�
	int case5();

	//��ʼָ������
	int case6();

	//����ָ������
	int case7();

	//�Զ���ʼ�½���
	int case8();

	//�˳�ϵͳ
	int case9();

	ProcessList pl;
	FreePartition fp;
	AllocPartition ap;

	//�Զ���ʼ�½��̱�־��0�رգ�1��
	static int AUTO_STARTING_PROCESS_FLAG;
};
