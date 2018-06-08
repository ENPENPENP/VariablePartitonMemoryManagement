#include "stdafx.h"
#include "FreePartition.h"
using namespace std;

int  FreePartition::FREE_PARTITION_LENGTH = 0;

FreePartition::FreePartition()
{
	head = NULL;
}

FreePartition::~FreePartition()
{
	freePartition *temp;
	if (head != NULL) {
		for (; head->next != NULL;)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
}

//�ָ����
void FreePartition::cutFreePartition(int freepartitionsize, int startaddr, int needsize)
{
	freePartition *temp = head;
	//freePartition *mark;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			//����ǰ��������������������ֱ���޸ĵ�ǰ������Ϣ
			if (temp->startAddr == startaddr) {
				//�����˷�ϵͳ��Դ
				//mark = new freePartition((freepartitionsize - needsize), (startaddr + needsize));
				temp->freePartitionSize = (freepartitionsize - needsize);
				temp->startAddr = (startaddr + needsize);
				flag = 1;
				break;
			}
			//û���õ��ж�
			//if (temp->next->startAddr == startaddr) {
			//	mark = new freePartition((freepartitionsize - needsize), (startaddr + needsize));
			//	mark->next = temp->next->next;
			//	temp->next = mark;
			//}
			if (temp->next == NULL)
				break;
			else
				temp = temp->next;
		}
		if (flag == 0) throw errorFlag = -3;
	}
	catch (int ef) {
		throw ef;
	}
}

//ɾ������
void FreePartition::deletePartition(int size, int addr)
{
	freePartition *temp = head;
	freePartition *mark = NULL;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;

		while (1) {
			//�ж�ͷָ��
			if (temp == head) {
				//����ͷָ���ҷ���������ֱ���޸�ͷָ��ָ��ɾ��ԭ����
				if (temp->freePartitionSize == size && temp->startAddr == addr) {
					//��markָ��ָ����һ������
					mark = head->next;
					//ɾ��ͷָ��ָ��ķ���
					delete head;
					//�ٽ�ͷָ��ָ��ԭ��������һ������
					head = mark;
					flag = 1;
					break;
				}
			}
			//������ͷָ���������ж�
			else if (temp->next->freePartitionSize == size && temp->next->startAddr == addr) {
				//��markָ��temp->next����һ����
				mark = temp->next->next;
				//ɾ����ǰָ��ָ��ķ���
				delete temp->next;
				//�ٽ���ǰָ��ָ��ԭ��������һ������
				temp->next = mark;
				flag = 1;
				break;
			}
			if (temp->next == NULL)
				break;
			else
				temp = temp->next;
		}
		if (flag == 0) throw errorFlag = -3;
	}
	catch (int ef) {
		throw ef;
	}
}

//���Ʒ�����Ϣ
//freePartition*  FreePartition::copyPartitionInfo(freePartition *point)
//{
//	freePartition *temp = new freePartition(point->freePartitionSize, point->startAddr);
//	return temp;
//}

//���з�����ʼ��
void FreePartition::freePartitionInit()
{
	head = new freePartition(maxMemory_KB, 0);
	FreePartition::FREE_PARTITION_LENGTH++;
}

//�������
void FreePartition::showList()
{
	freePartition *temp = head;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;

		cout << "startAddress" << "\t" << "size" << endl;
		while (1) {
			cout << temp->startAddr << "\t\t" << temp->freePartitionSize << " KB" << endl;
			if (temp->next == NULL)
				break;
			else
				temp = temp->next;
		}
	}
	catch (int ef) {
		throw ef;
	}
}

//���ڷ����ϲ�
void FreePartition::freePartitionMerge()
{
	freePartition *temp = head;
	freePartition *mark;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			if (temp->next != NULL) {
				//�ϲ�������ɾ������ķ���
				if ((temp->startAddr + temp->freePartitionSize) == temp->next->startAddr) {
					temp->freePartitionSize += temp->next->freePartitionSize;
					mark = temp->next->next;
					delete temp->next;
					temp->next = mark;
					FreePartition::FREE_PARTITION_LENGTH--;
					break;
				}
				else
					temp = temp->next;
			}
			if (temp->next == NULL)
				break;
		}
	}
	catch (int ef) {
		throw ef;
	}
}

void FreePartition::freePartitonSort()
{
	freePartition *Node1 = head;
	freePartition *Node2 = NULL;

	int errorFlag = 0;
	try {
		if (head == NULL) throw errorFlag = -2;
		if (head->next == NULL) throw errorFlag = -4;
		freePartition temp;

		//�����ð�������㷨
		//for (;Node1->next->next != NULL;Node1 = Node1->next) {
		//	for (;Node2->next->next != Node1; Node2 = Node2->next) {
		//		if (Node1->freePartitionSize < Node2->freePartitionSize) {
		//			//����������С
		//			temp.freePartitionSize = Node1->freePartitionSize;
		//			Node1->freePartitionSize = Node2->freePartitionSize;
		//			Node2->freePartitionSize = temp.freePartitionSize;
		//			//����������ʼ��ַ
		//			temp.startAddr = Node1->startAddr;
		//			Node1->startAddr = Node2->startAddr;
		//			Node2->startAddr = temp.startAddr;
		//		}
		//	}
		//}

		while (Node1 != Node2)
		{
			while (Node1->next != Node2)
			{
				if (Node1->freePartitionSize > Node1->next->freePartitionSize)
				{
					//����������С
					temp.freePartitionSize = Node1->freePartitionSize;
					Node1->freePartitionSize = Node1->next->freePartitionSize;
					Node1->next->freePartitionSize = temp.freePartitionSize;
					//����������ʼ��ַ
					temp.startAddr = Node1->startAddr;
					Node1->startAddr = Node1->next->startAddr;
					Node1->next->startAddr = temp.startAddr;
				}
				Node1 = Node1->next;
			}
			Node2 = Node1;
			Node1 = head;
		}
	}
	catch (int ef) {
		if (errorFlag == -2) throw ef;
		if (errorFlag == -4);
	}
}

//�����������ܴ�С
int FreePartition::freePartitionRemain()
{
	freePartition *temp = head;
	int fpr = 0;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			fpr += temp->freePartitionSize;
			if (temp->next == NULL)
				break;
			else
				temp = temp->next;
		}
		return fpr;
	}
	catch (int ef) {
		throw ef;
	}
}