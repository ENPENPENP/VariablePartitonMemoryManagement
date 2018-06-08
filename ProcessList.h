#pragma once
#include "List.h"
using namespace std;

/*
表示进程的结构体
*/
struct processList {
	//进程序列号
	int proID;
	//所需内存
	int needMemo;
	//起始地址
	int startAddr;
	//状态标志，0表示等待，1表示运行中
	int State;
	//指向下一个进程的指针
	processList *next;
	//链表初始化
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
定义进程类
*/
class ProcessList :
	public List
{
public:
	ProcessList();
	virtual ~ProcessList();

	//进程链表初始化
	void processListInit();

	//输出链表
	void showList();

	//删除进程
	void deleteProcess(processList *);

	//查找分区，获取分区信息
	processList * ListFind(int);

	//加入新进程
	void processInsert(int, int);

	//等待进程数
	static  int  PROCESS_LIST_LENGTH;

	//进程链表头指针
	processList *head;
};
