#include "stdafx.h"
#include "ListOperation.h"
using namespace std;

//默认置零
int ListOperation::AUTO_STARTING_PROCESS_FLAG = 0;

ListOperation::ListOperation()
{
}

ListOperation::~ListOperation()
{
}

//开始进程
void ListOperation::startProcess(int pid)
{
	int errorFlag = 0;
	//获取进程信息
	processList *temp = pl.ListFind(pid);
	try {
		//检查空闲分区大小是否足够
		if (temp->needMemo > fp.freePartitionRemain()) throw errorFlag = -1;
		//状态标志置1，表示正在运行
		temp->State = 1;
		//为进程分配空闲分区，并获取分区信息
		giveFreePartition(temp);
		//将分配的分区指针和进程id作参数传递进函数
		moveProcessToAllocPartition(temp);
		//空闲分区合并
		fp.freePartitionMerge();
		//空闲分区排序
		fp.freePartitonSort();
	}
	catch (int ef) {
		throw ef;
	}
}

//将进程移入已分配分区链表
void ListOperation::moveProcessToAllocPartition(processList  *pl)
{
	allocPartition *flag = new allocPartition(pl->proID, pl->needMemo, pl->startAddr);
	allocPartition *temp = ap.head;
	int endflag = 1;
	if (ap.head == NULL) {
		ap.head = flag;
		flag->next = NULL;
		endflag = 0;
	}
	while (endflag) {
		if (temp->next == NULL) {
			temp->next = flag;
			flag->next = NULL;
			break;
		}
		else
			temp = temp->next;
	}
	AllocPartition::ALLOC_PARTITION_LENGTH++;
}

//回收刚释放的分区
void ListOperation::partitionRecyle(allocPartition *flag)
{
	/*
	先插入到链表中，先合并再排序
	*/

	freePartition *mark = fp.head;
	freePartition *temp = NULL;

	int errorFlag = 0;
	try {
		int Flag = 0;
		//插入到队列中，如果有相邻的分区直接合并，且Flag变为非0数
		while (1) {
			//此情况是新分区的起始地址在当前遍历分区之前
			//将新分区空间大小加入到当前遍历的分区，新分区的起始地址赋给当前遍历分区
			if (flag->allocPartitionSize + flag->startAddr == mark->startAddr) {
				mark->freePartitionSize += flag->allocPartitionSize;
				mark->startAddr = flag->startAddr;
				fp.head = mark;
				//flag置1代表已合并
				Flag = 1;
				break;
			}
			//此情况是新分区的起始地址在当前遍历分区之后
			//将新分区空间大小加入到当前遍历分区，然后直接将新分区删除
			if (mark->freePartitionSize + mark->startAddr == flag->startAddr) {
				mark->freePartitionSize += flag->allocPartitionSize;
				//flag置1代表已合并
				Flag = 1;
				break;
			}
			//Flag若为0则表示没有插入到链表中，所以将其放到链表末尾
			if (mark->next == NULL && Flag == 0) {
				//在空闲分区链表中新建分区
				temp = new freePartition(flag->allocPartitionSize, flag->startAddr);
				mark->next = temp;
				break;
			}
			else
				mark = mark->next;
		}
	}
	catch (int ef) {
		throw ef;
	}
}

//结束进程
void ListOperation::endProcess(int pid)
{
	allocPartition *temp = NULL;
	processList *mark = NULL;
	allocPartition *flag;
	int errorFlag = 0;
	try {
		//删除进程
		mark = pl.ListFind(pid);
		pl.deleteProcess(mark);
		//查找进程对应的指针
		temp = ap.ListFind(pid);
		//回收分区
		partitionRecyle(temp);
		//删除已分配分区中要释放的分区
		ap.deleteUsedPartition(temp);
		//空闲分区合并
		fp.freePartitionMerge();
		//按分区大小排序
		fp.freePartitonSort();
	}
	catch (int ef) {
		throw ef;
	}
}

//是否自动开始新进程
void ListOperation::autoStartNewProcess()
{
	int flag = 1;
	char p;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Auto start New Process" << endl;
		cout << "Staus:";
		//在0和1之间切换
		if (ListOperation::AUTO_STARTING_PROCESS_FLAG == 0)
			cout << " Closed" << endl;
		else cout << " Opened" << endl;
		if (ListOperation::AUTO_STARTING_PROCESS_FLAG == 0)
			cout << "Do you want to open it?" << endl;
		else
			cout << "Do you want to close it?" << endl;
		cout << "Enter [Y/N]:	" << endl;
		p = operationInput();
		if (p == 'Y' || p == 'y') {
			if (ListOperation::AUTO_STARTING_PROCESS_FLAG == 0) {
				ListOperation::AUTO_STARTING_PROCESS_FLAG = 1;
				cout << "\n" << "Open successful!" << endl;
				break;
			}
			else {
				ListOperation::AUTO_STARTING_PROCESS_FLAG = 0;
				cout << "\n" << "Close successful!" << endl;
				break;
			}
		}
		if (p == 'N' || p == 'n') {
			break;
		}
		if (p != 'Y'&&p != 'y'&&p != 'N'&&p != 'n') {
			cout << "Please input Y or N!" << endl;
			system("pause");
			continue;
		}
	}
}

//首页菜单
void ListOperation::menu()
{
	cout << "******************************************************" << endl;
	cout << "		1.New Process					 " << endl;
	cout << "		2.Delete Process				 " << endl;
	cout << "		3.Check Process List			 " << endl;
	cout << "		4.Check Free Partition			 " << endl;
	cout << "		5.Check the Alloced Partition	 " << endl;
	cout << "		6.Start Process					 " << endl;
	cout << "		7.End Process					 " << endl;
	cout << "		8.Auto start New Process		 " << endl;
	cout << "		9.Quit System					 " << endl;
	cout << "******************************************************" << endl;
}

//首页
int ListOperation::Index()
{
	int op = -1;
	int errorFlag = 0;

	//循环直到return -1
	while (1) {
		errorFlag = 0;
		system("cls");
		menu();
		cout << "Input your option:" << endl;
		op = opInput();
		try {
			switch (op) {
				//开始新进程
			case(1): {
				errorFlag = case1();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //删除进程
			case(2): {
				errorFlag = case2();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //查看进程列表
			case(3): {
				errorFlag = case3();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //查看空闲分区列表
			case(4): {
				errorFlag = case4();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //查看已分配分区列表
			case(5): {
				errorFlag = case5();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //开始指定进程
			case(6): {
				errorFlag = case6();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //结束指定进程
			case(7): {
				errorFlag = case7();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //自动开始新进程
			case(8): {
				errorFlag = case8();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //退出系统
			case(9): {
				errorFlag = case9();
				if (errorFlag == -1) {
					system("cls");
					menu();
					cout << endl;
					cout << "Thanks for using the VPMM system!" << endl;
					cout << endl;
					cout << "Press any key to quit." << endl;
					getchar();
					getchar();
					return -1;
				}
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
			}
		}
		catch (int ef) {
			if (ef == -1)
				cout << "Error: Request Memory Outline!" << endl;
			if (ef == -2)
				cout << "Error: List is empty!" << endl;
			if (ef == -3)
				cout << "Error: Can not find the partition or process! " << endl;
			if (ef == -4)
				cout << "Error: Can not sort the list! " << endl;
			if (ef == -5)
				cout << "Error: The max capacity is 10!" << endl;
			cout << "\n" << endl;
			cout << "Press any key to back." << endl;
			getchar();
			getchar();
		}
	}
}

int ListOperation::opInput()
{
	int op;
	cin >> op;
	while (cin.rdstate() == ios_base::failbit) {
		cout << "Please input integer number：" << endl;
		cin.clear();
		cin.ignore(2, '\n');
		cin >> op;
	}
	while (op <= 0 || op > 9) {
		cout << "Please input correct number between [0-9] :" << endl;
		cin >> op;
		while (cin.rdstate() == ios_base::failbit) {
			cout << "Please input integer number：" << endl;
			cin.clear();
			cin.ignore(2, '\n');
			cin >> op;
		}
	}
	return op;
}

int ListOperation::pidInput()
{
	int pid;
	cin >> pid;
	while (cin.rdstate() == ios_base::failbit) {
		cout << "Please input integer number：" << endl;
		cin.clear();
		cin.ignore(5, '\n');
		cin >> pid;
	}
	return pid;
}

int ListOperation::sizeInput()
{
	int size;
	cin >> size;
	while (cin.rdstate() == ios_base::failbit) {
		cout << "Please input integer number：" << endl;
		cin.clear();
		cin.ignore(5, '\n');
		cin >> size;
	}
	while (size >= maxMemory_KB || size >= fp.freePartitionRemain()) {
		cout << "Error:The Max Memory is 10240KB!" << "\n" << endl;
		cout << "Please input a number smaller than 10240:" << endl;
		cin.clear();
		cin.ignore(5, '\n');
		cin >> size;
		while (cin.rdstate() == ios_base::failbit) {
			cout << "Please input integer number：" << endl;
			cin.clear();
			cin.ignore(5, '\n');
			cin >> size;
		}
	}
	return size;
}

char ListOperation::operationInput()
{
	char p;
	cin >> p;
	while (cin.rdstate() == ios::failbit) {
		cout << "Please input Y or N!" << endl;
		cin.clear();
		cin.ignore(2, '\n');
		cin >> p;
	}
	return p;
}

//加入新进程
int ListOperation::case1()
{
	int pid, size;
	int errorFlag = 0;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: New Process" << endl;
		if (PROCESS_LIST_LENGTH >= 10) throw errorFlag = -5;
		cout << "Process existed:" << PROCESS_LIST_LENGTH << endl;
		cout << "Input the ID of Process(the max capacity is 10):";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//输入0跳出函数
		if (pid == 0) return 0;
		processList *mark;
		int i = 0;
		try {
			//在链表进程中查找是否有相同id的进程,若不存在则抛出错误
			//我们拦截这个错误，自行处理，使用这个错误跳过下面的if判断语句
			mark = pl.ListFind(pid);
			//若成功找到进程则将i置1
			i = 1;
			//如果i的值为1，则表示进程列表中存在相同id的进程，跳出循环重新输入
			if (i == 1) {
				cout << "\n" << "Error: The ID was used!" << "\n" << endl;
				cout << endl;
				cout << "Press any key to continue." << endl;
				getchar();
				getchar();
				continue;
			}
		}
		catch (int ef) {
			//拦截捕捉到的链表为空和找不到进程的错误，因为这两种情况都表示进程链表中没有相同id的进程
			//所以程序可以继续指执行
			if (ef == -3 || ef == -2)
				;
		}
		cout << "Input the needed Memory of Process(The max Memory is 10240KB):";
		cout << "[Enter 0 to back]" << endl;
		size = sizeInput();
		if (size == 0) return 0;
		pl.processInsert(pid, size);
		//自动开启进程
		if (ListOperation::AUTO_STARTING_PROCESS_FLAG == 1)
			startProcess(pid);
		cout << "\n" << "Add new process successful!" << endl;
		return 1;
	}
}
//删除进程
int ListOperation::case2()
{
	int pid;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Delete Process" << endl;
		pl.showList();
		cout << "Input the ID of Process:";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//输入0跳出函数
		if (pid == 0) return 0;
		processList *temp;
		try {
			temp = pl.ListFind(pid);
			if (temp->State == 1) {
				cout << "\n" << "Error: Process is working!" << endl;
				cout << endl;
				cout << "Press any key to continue." << endl;
				getchar();
				getchar();
				continue;
			}
			else {
				pl.deleteProcess(temp);
				cout << "\n" << "Process was deleted!" << endl;
				break;
			}
		}
		catch (int ef) {
			throw ef;
		}
	}
	return 1;
}

//查看进程列表
int ListOperation::case3()
{
	system("cls");
	menu();
	cout << "Your option: Check Process List" << endl;
	//打印进程链表
	pl.showList();
	return 1;
}

//查看空闲分区列表
int ListOperation::case4()
{
	system("cls");
	menu();
	cout << "Your option: Check Free Partition" << endl;
	//打印空闲分区链表
	fp.showList();
	return 1;
}

//查看已分配分区列表
int ListOperation::case5()
{
	system("cls");
	menu();
	cout << "Your option: Check the Alloced Partition" << endl;
	ap.showList();
	return 1;
}

//开始指定进程
int ListOperation::case6()
{
	int pid;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Start Process" << endl;
		//开始进程
		pl.showList();
		cout << "Input the ID of Process:";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//输入0跳出函数
		if (pid == 0) return 0;
		processList *flag = pl.ListFind(pid);
		if (flag->State == 1) {
			cout << "Process is working!" << endl;
			cout << "Please input an other process ID!" << endl;
			cout << endl;
			cout << "Press any key to continue." << endl;
			getchar();
			getchar();
			continue;
		}
		else {
			startProcess(pid);
			break;
		}
	}
	cout << "\n" << "Process is working!" << endl;
	return 1;
}

//结束指定进程
int ListOperation::case7()
{
	int pid;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: End Process" << endl;
		//结束进程
		pl.showList();
		cout << "Input the ID of Process:";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//输入0跳出函数
		if (pid == 0) return 0;
		try {
			processList *temp = pl.ListFind(pid);
			if (temp->State == 0) {
				cout << "The Process(" << pid << ") is not processing!" << endl;
				cout << endl;
				cout << "Press any key to continue." << endl;
				getchar();
				getchar();
				continue;
			}
			else {
				endProcess(pid);
				break;
			}
		}
		catch (int ef) {
			if (ef == -3) throw ef;
		}
	}
	cout << "\n" << "Process was ended!" << endl;
	return 1;
}

//自动开始新进程
int ListOperation::case8()
{
	autoStartNewProcess();
	return 1;
}

//退出系统
int ListOperation::case9()
{
	char p;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Quit System" << endl;
		cout << "Do you want to quit?" << endl;
		cout << "Enter [Y/N]:	" << endl;
		p = operationInput();
		if (p == 'Y' || p == 'y') {
			return -1;
		}
		if (p == 'N' || p == 'n')
			break;
		if (p != 'Y'&&p != 'y'&&p != 'N'&&p != 'n') {
			cout << "Please input Y or N!" << endl;
			cout << endl;
			cout << "Press any key to continue." << endl;
			getchar();
			getchar();
			continue;
		}
	}
	return 1;
}

//分配空闲分区
void ListOperation::giveFreePartition(processList *plpointer)
{
	freePartition *temp = fp.head;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		//判断分割后的剩余分区大小是否大于最小碎片大小
		while (1) {
			//查找合适的分区
			if (temp->freePartitionSize > plpointer->needMemo) {
				//定义碎片最小容量
				//const int minPartitonSize = 50;
				//若分割后的剩余分区大于最小碎片容量50，将剩余大小的分区作为新的空闲分区
				if ((temp->freePartitionSize - plpointer->needMemo) > minPartitonSize) {
					plpointer->startAddr = temp->startAddr;
					//将找到的适合的空闲分区的大小，起始地址，还有所需分配的分区大小作为参数
					//返回分割后的分区指针，包含分区大小
					fp.cutFreePartition(temp->freePartitionSize, temp->startAddr, plpointer->needMemo);
					flag = 1;
				}
				//若分割后的剩余分区小于最小碎片最小容量，直接将整个分区给进程，然后将该分区从空闲分区链表中删除
				else if ((temp->freePartitionSize - plpointer->needMemo) <= minPartitonSize) {
					plpointer->startAddr = temp->startAddr;
					//删除分区
					fp.deletePartition(temp->freePartitionSize, temp->startAddr);
					flag = 1;
				}
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