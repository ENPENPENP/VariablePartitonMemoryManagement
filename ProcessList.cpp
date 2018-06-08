#include "stdafx.h"
#include "ProcessList.h"
using namespace std;

int ProcessList::PROCESS_LIST_LENGTH = 0;

ProcessList::ProcessList()
{
	head = NULL;
}

ProcessList::~ProcessList()
{
	processList *temp;
	if (head != NULL) {
		for (; head->next != NULL;)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
}

//进程链表初始化
void ProcessList::processListInit()
{
	head = NULL;
}

//输出链表
void ProcessList::showList()
{
	processList *temp = head;

	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		cout << "processID" << "\t" << "needMemory" << "\t" << "state" << "\t\t" << "startAddress" << endl;
		while (1)
		{
			cout << temp->proID << "\t\t";
			cout << temp->needMemo << " KB" << "\t\t";
			if (temp->State == 0)
				cout << "waiting" << "\t\t" << "null" << endl;
			else
				cout << "processing" << "\t" << temp->startAddr << endl;

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

void ProcessList::deleteProcess(processList *temp)
{
	processList *mark = head;
	processList *flag;

	int errorFlag = 0;
	try {
		if (mark == NULL) throw errorFlag = -2;
		while (1) {
			if (mark == head) {
				if (mark->proID == temp->proID) {
					flag = head->next;
					delete mark;
					mark = NULL;
					head = flag;
					PROCESS_LIST_LENGTH--;
					break;
				}
			}
			if (mark->next != NULL) {
				if (mark->next->proID == temp->proID) {
					flag = mark->next->next;
					delete mark->next;
					mark->next = NULL;
					mark->next = flag;
					PROCESS_LIST_LENGTH--;
					break;
				}
			}
			if (mark->next == NULL)
				break;
			else
				mark = mark->next;
		}
	}
	catch (int ef) {
		throw ef;
	}
}

//查找分区，获取分区信息
processList * ProcessList::ListFind(int pid)
{
	processList *temp = head;

	int errorFlag = 0;
	try {
		if (head == NULL) throw errorFlag = -2;
		while (1) {
			if (temp->proID == pid) {
				return temp;
			}
			if (temp->next == NULL) {
				throw errorFlag = -3;
			}
			else
				temp = temp->next;
		}
	}
	catch (int ef) {
		throw ef;
	}
}

void ProcessList::processInsert(int pid, int size)
{
	processList *mark = head;
	processList *temp = new processList(pid, size);
	int errorFlag = 0;
	try {
		if (ProcessList::PROCESS_LIST_LENGTH + 1 > 10) throw errorFlag = -5;
		while (1) {
			if (head == NULL) {
				head = temp;
				head->next = NULL;
				break;
			}
			if (mark->next == NULL) {
				mark->next = temp;
				temp->next = NULL;
				break;
			}
			else
				mark = mark->next;
		}
		ProcessList::PROCESS_LIST_LENGTH++;
	}
	catch (int ef) {
		delete temp;
		throw ef;
	}
}