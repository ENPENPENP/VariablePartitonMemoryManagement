#pragma once
#include"ProcessList.h"
#include"FreePartition.h"
#include"AllocPartition.h"
using namespace std;

/*
定义最终操作类
*/
class ListOperation :
	public ProcessList, FreePartition, AllocPartition
{
public:
	ListOperation();
	~ListOperation();

	//分配空闲分区
	void giveFreePartition(processList *);

	//开始进程
	void startProcess(int);

	//将进程移入已分配分区链表
	void moveProcessToAllocPartition(processList *);

	//回收刚释放的分区
	void partitionRecyle(allocPartition *);

	//结束进程
	void endProcess(int);

	//是否自动开始新进程
	void autoStartNewProcess();

	//菜单
	void menu();

	//首页
	int Index();

	//输入选项op
	int opInput();

	//输入pid
	int pidInput();

	//输入分区大小
	int sizeInput();

	//输入Y/N操作
	char operationInput();

	//开始新进程
	int case1();

	//删除进程
	int case2();

	//查看进程列表
	int case3();

	//查看空闲分区列表
	int case4();

	//查看已分配分区列表
	int case5();

	//开始指定进程
	int case6();

	//结束指定进程
	int case7();

	//自动开始新进程
	int case8();

	//退出系统
	int case9();

	ProcessList pl;
	FreePartition fp;
	AllocPartition ap;

	//自动开始新进程标志，0关闭，1打开
	static int AUTO_STARTING_PROCESS_FLAG;
};
