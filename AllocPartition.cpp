#include "stdafx.h"
#include "AllocPartition.h"
using namespace std;

int AllocPartition::ALLOC_PARTITION_LENGTH = 0;

AllocPartition::AllocPartition()
{
	head = NULL;
}

AllocPartition::~AllocPartition()
{
	allocPartition *temp;
	if (head != NULL) {
		for (; head->next != NULL;)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
}
//���Ʒ�����Ϣ
//allocPartition * AllocPartition::copyPartitionInfo(allocPartition *point)
//{
//	allocPartition *temp = new allocPartition(point->usingProcessID, point->allocPartitionSize, point->startAddr);
//	return temp;
//}

//�ѷ��������ʼ��
void AllocPartition::allocPartittionInit()
{
	head = NULL;
}

//ɾ���ͷŵķ���
void AllocPartition::deleteUsedPartition(allocPartition *flag)
{
	int errorFlag = 0;
	int Flag = 0;
	allocPartition *temp = head;
	allocPartition *mark = NULL;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			//ͷָ���ж�
			if (temp == head) {
				if (temp->usingProcessID == flag->usingProcessID) {
					//������һ��ָ��ָ��head->next����һ������
					mark = head->next;
					//ɾ��temp����
					delete temp;
					temp = NULL;
					//��ͷָ���ָ����Ϊ�ҵ���������һ������
					head = mark;
					//�ѷ���������ȼ�1
					AllocPartition::ALLOC_PARTITION_LENGTH--;
					Flag = 1;
					break;
				}
			}
			if (temp->next != NULL) {
				if (temp->next->usingProcessID == flag->usingProcessID) {
					//������һ��ָ��ָ��temp->next����һ������
					mark = temp->next->next;
					//ɾ��temp->next����
					delete temp->next;
					//������ָ��ָ��
					temp->next = mark;
					//�ѷ���������ȼ�1
					AllocPartition::ALLOC_PARTITION_LENGTH--;
					Flag = 1;
					break;
				}
			}
			if (temp->next == NULL)
				break;
			else {
				temp = temp->next;
			}
		}

		if (Flag == 0) throw errorFlag = -3;
	}
	catch (int ef) {
		throw ef;
	}
}

//�������
void AllocPartition::showList()
{
	allocPartition *temp = head;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		cout << "processID" << "\t" << "partitionSize" << "\t" << "starAddress" << endl;
		while (1) {
			cout << temp->usingProcessID << "\t\t" << temp->allocPartitionSize;
			cout << " KB" << "\t\t" << temp->startAddr << endl;
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

//���ҷ�������ȡ������Ϣ
allocPartition * AllocPartition::ListFind(int pid)
{
	allocPartition *temp = head;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;

		while (1) {
			//��ѯ����ͬid�ķ����������ַ
			if (temp->usingProcessID == pid) {
				return temp;
			}
			if (temp->next == NULL) {
				errorFlag = -3;
				break;
			}
			else
				temp = temp->next;
		}
		//û���ҵ����׳�����
		if (errorFlag == -3) throw errorFlag;
	}
	catch (int ef) {
		throw ef;
	}
}