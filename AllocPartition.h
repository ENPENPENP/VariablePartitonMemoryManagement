#pragma once
#include "List.h"
using namespace std;

/*
已分配分区结构体
*/
struct allocPartition {
	//存放占用分区的进程ID
	int usingProcessID;
	//已分配分区大小
	int allocPartitionSize;
	//起始地址
	int startAddr;
	//指向下一个碎片的指针
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
定义已分配分区链表类
*/
class AllocPartition :
	public List
{
public:
	AllocPartition();
	virtual ~AllocPartition();

	//复制分区信息
	//allocPartition *  copyPartitionInfo(allocPartition *);

	//已分配分区初始化
	void allocPartittionInit();

	//删除已释放的分区
	void deleteUsedPartition(allocPartition *);

	//输出链表
	void showList();

	//定义已分配分区数
	static int  ALLOC_PARTITION_LENGTH;

	//查找分区，获取分区信息
	allocPartition* ListFind(int);

	//定义头指针
	allocPartition *head;
};
