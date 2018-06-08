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
//复制分区信息
//allocPartition * AllocPartition::copyPartitionInfo(allocPartition *point)
//{
//	allocPartition *temp = new allocPartition(point->usingProcessID, point->allocPartitionSize, point->startAddr);
//	return temp;
//}

//已分配分区初始化
void AllocPartition::allocPartittionInit()
{
	head = NULL;
}

//删除释放的分区
void AllocPartition::deleteUsedPartition(allocPartition *flag)
{
	int errorFlag = 0;
	int Flag = 0;
	allocPartition *temp = head;
	allocPartition *mark = NULL;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			//头指针判断
			if (temp == head) {
				if (temp->usingProcessID == flag->usingProcessID) {
					//用另外一个指针指向head->next的下一个分区
					mark = head->next;
					//删除temp分区
					delete temp;
					temp = NULL;
					//将头指针的指向变更为找到分区的下一个分区
					head = mark;
					//已分配分区长度减1
					AllocPartition::ALLOC_PARTITION_LENGTH--;
					Flag = 1;
					break;
				}
			}
			if (temp->next != NULL) {
				if (temp->next->usingProcessID == flag->usingProcessID) {
					//用另外一个指针指向temp->next的下一个分区
					mark = temp->next->next;
					//删除temp->next分区
					delete temp->next;
					//在重新指向指针
					temp->next = mark;
					//已分配分区长度减1
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

//输出链表
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

//查找分区，获取分区信息
allocPartition * AllocPartition::ListFind(int pid)
{
	allocPartition *temp = head;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;

		while (1) {
			//查询到相同id的分区后输入地址
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
		//没有找到则抛出错误
		if (errorFlag == -3) throw errorFlag;
	}
	catch (int ef) {
		throw ef;
	}
}