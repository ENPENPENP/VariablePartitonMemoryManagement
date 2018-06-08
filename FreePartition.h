#pragma once
#include "List.h"
using namespace std;

/*
空闲分区结构体
*/
struct freePartition {
	//分区大小
	int freePartitionSize;
	//起始地址
	int startAddr;
	//指向下一个分区的指针
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
定义空闲分区链表类
*/
class FreePartition :
	public List
{
public:

	FreePartition();
	virtual ~FreePartition();

	//分割分区
	void cutFreePartition(int, int, int);

	//删除分区
	void deletePartition(int, int);

	//复制分区信息
	//freePartition *  copyPartitionInfo(freePartition *);

	//空闲分区初始化
	void freePartitionInit();

	//输出链表
	void showList();

	//相邻分区合并
	void freePartitionMerge();

	//空闲分区排序
	void freePartitonSort();

	//计算空余分区总大小
	int freePartitionRemain();

	//定义空闲分区的分区数
	static int  FREE_PARTITION_LENGTH;

	//定义头指针
	freePartition *head;
};
