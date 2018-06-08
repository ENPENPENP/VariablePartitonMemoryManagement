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

//分割分区
void FreePartition::cutFreePartition(int freepartitionsize, int startaddr, int needsize)
{
	freePartition *temp = head;
	//freePartition *mark;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			//若当前遍历分区符合条件，则直接修改当前分区信息
			if (temp->startAddr == startaddr) {
				//纯属浪费系统资源
				//mark = new freePartition((freepartitionsize - needsize), (startaddr + needsize));
				temp->freePartitionSize = (freepartitionsize - needsize);
				temp->startAddr = (startaddr + needsize);
				flag = 1;
				break;
			}
			//没有用的判断
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

//删除分区
void FreePartition::deletePartition(int size, int addr)
{
	freePartition *temp = head;
	freePartition *mark = NULL;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;

		while (1) {
			//判断头指针
			if (temp == head) {
				//若是头指针且符合条件则直接修改头指针指向并删除原分区
				if (temp->freePartitionSize == size && temp->startAddr == addr) {
					//用mark指针指向下一个分区
					mark = head->next;
					//删除头指针指向的分区
					delete head;
					//再将头指针指向原分区的下一个分区
					head = mark;
					flag = 1;
					break;
				}
			}
			//若不是头指针再重新判断
			else if (temp->next->freePartitionSize == size && temp->next->startAddr == addr) {
				//用mark指向temp->next的下一分区
				mark = temp->next->next;
				//删除当前指针指向的分区
				delete temp->next;
				//再将当前指针指向原分区的下一个分区
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

//复制分区信息
//freePartition*  FreePartition::copyPartitionInfo(freePartition *point)
//{
//	freePartition *temp = new freePartition(point->freePartitionSize, point->startAddr);
//	return temp;
//}

//空闲分区初始化
void FreePartition::freePartitionInit()
{
	head = new freePartition(maxMemory_KB, 0);
	FreePartition::FREE_PARTITION_LENGTH++;
}

//输出链表
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

//相邻分区合并
void FreePartition::freePartitionMerge()
{
	freePartition *temp = head;
	freePartition *mark;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		while (1) {
			if (temp->next != NULL) {
				//合并分区，删除后面的分区
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

		//错误的冒泡排序算法
		//for (;Node1->next->next != NULL;Node1 = Node1->next) {
		//	for (;Node2->next->next != Node1; Node2 = Node2->next) {
		//		if (Node1->freePartitionSize < Node2->freePartitionSize) {
		//			//交换分区大小
		//			temp.freePartitionSize = Node1->freePartitionSize;
		//			Node1->freePartitionSize = Node2->freePartitionSize;
		//			Node2->freePartitionSize = temp.freePartitionSize;
		//			//交换分区起始地址
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
					//交换分区大小
					temp.freePartitionSize = Node1->freePartitionSize;
					Node1->freePartitionSize = Node1->next->freePartitionSize;
					Node1->next->freePartitionSize = temp.freePartitionSize;
					//交换分区起始地址
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

//计算空余分区总大小
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