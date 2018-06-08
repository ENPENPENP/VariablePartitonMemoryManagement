// VariablePartitonMemoryManagement.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"ListOperation.h"
using namespace std;

int main()
{
	ListOperation lo;
	//初始化进程，空闲分区和已分配分区链表
	lo.pl.processListInit();
	lo.fp.freePartitionInit();
	lo.ap.allocPartittionInit();

	int flag = 0;
	while (!flag) {
		flag = lo.Index();
	}
	return 0;
}