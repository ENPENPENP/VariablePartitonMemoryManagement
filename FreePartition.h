#pragma once
#include "List.h"
using namespace std;

/*
���з����ṹ��
*/
struct freePartition {
	//������С
	int freePartitionSize;
	//��ʼ��ַ
	int startAddr;
	//ָ����һ��������ָ��
	freePartition *next;

	//
	freePartition() {
		freePartitionSize = 0;
		startAddr = 0;
		startAddr = NULL;
	};
	freePartition(int size, int startaddr) : freePartitionSize(size), startAddr(startaddr) {
		next = NULL;
	}
};
/*
������з���������
*/
class FreePartition :
	public List
{
public:

	FreePartition();
	virtual ~FreePartition();

	//�ָ����
	void cutFreePartition(int, int, int);

	//ɾ������
	void deletePartition(int, int);

	//���Ʒ�����Ϣ
	//freePartition *  copyPartitionInfo(freePartition *);

	//���з�����ʼ��
	void freePartitionInit();

	//�������
	void showList();

	//���ڷ����ϲ�
	void freePartitionMerge();

	//���з�������
	void freePartitonSort();

	//�����������ܴ�С
	int freePartitionRemain();

	//������з����ķ�����
	static int  FREE_PARTITION_LENGTH;

	//����ͷָ��
	freePartition *head;
};
