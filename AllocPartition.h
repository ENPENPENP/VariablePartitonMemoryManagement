#pragma once
#include "List.h"
using namespace std;

/*
�ѷ�������ṹ��
*/
struct allocPartition {
	//���ռ�÷����Ľ���ID
	int usingProcessID;
	//�ѷ��������С
	int allocPartitionSize;
	//��ʼ��ַ
	int startAddr;
	//ָ����һ����Ƭ��ָ��
	allocPartition *next;
	//
	allocPartition() {
		startAddr = 0;
		allocPartitionSize = 0;
		startAddr = NULL;
	}
	allocPartition(int upid, int apsize, int startaddr) :
		usingProcessID(upid), allocPartitionSize(apsize), startAddr(startaddr) {}
};

/*
�����ѷ������������
*/
class AllocPartition :
	public List
{
public:
	AllocPartition();
	virtual ~AllocPartition();

	//���Ʒ�����Ϣ
	//allocPartition *  copyPartitionInfo(allocPartition *);

	//�ѷ��������ʼ��
	void allocPartittionInit();

	//ɾ�����ͷŵķ���
	void deleteUsedPartition(allocPartition *);

	//�������
	void showList();

	//�����ѷ��������
	static int  ALLOC_PARTITION_LENGTH;

	//���ҷ�������ȡ������Ϣ
	allocPartition* ListFind(int);

	//����ͷָ��
	allocPartition *head;
};
