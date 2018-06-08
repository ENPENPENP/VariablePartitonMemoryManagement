#pragma once
using namespace std;

//定义最大进程数
const int maxProcessNum = 10;
//定义总内存（KB）
const int maxMemory_KB = 10240;
//定义碎片最小容量
const int minPartitonSize = 50;

/*
定义链表操作基类
*/
class List
{
public:
	List();
	virtual ~List();

	//链表查找
	virtual void ListFind() {}

	//输出链表
	virtual void showList() = 0;
};
