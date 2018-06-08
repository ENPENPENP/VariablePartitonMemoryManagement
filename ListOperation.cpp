#include "stdafx.h"
#include "ListOperation.h"
using namespace std;

//Ĭ������
int ListOperation::AUTO_STARTING_PROCESS_FLAG = 0;

ListOperation::ListOperation()
{
}

ListOperation::~ListOperation()
{
}

//��ʼ����
void ListOperation::startProcess(int pid)
{
	int errorFlag = 0;
	//��ȡ������Ϣ
	processList *temp = pl.ListFind(pid);
	try {
		//�����з�����С�Ƿ��㹻
		if (temp->needMemo > fp.freePartitionRemain()) throw errorFlag = -1;
		//״̬��־��1����ʾ��������
		temp->State = 1;
		//Ϊ���̷�����з���������ȡ������Ϣ
		giveFreePartition(temp);
		//������ķ���ָ��ͽ���id���������ݽ�����
		moveProcessToAllocPartition(temp);
		//���з����ϲ�
		fp.freePartitionMerge();
		//���з�������
		fp.freePartitonSort();
	}
	catch (int ef) {
		throw ef;
	}
}

//�����������ѷ����������
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

//���ո��ͷŵķ���
void ListOperation::partitionRecyle(allocPartition *flag)
{
	/*
	�Ȳ��뵽�����У��Ⱥϲ�������
	*/

	freePartition *mark = fp.head;
	freePartition *temp = NULL;

	int errorFlag = 0;
	try {
		int Flag = 0;
		//���뵽�����У���������ڵķ���ֱ�Ӻϲ�����Flag��Ϊ��0��
		while (1) {
			//��������·�������ʼ��ַ�ڵ�ǰ��������֮ǰ
			//���·����ռ��С���뵽��ǰ�����ķ������·�������ʼ��ַ������ǰ��������
			if (flag->allocPartitionSize + flag->startAddr == mark->startAddr) {
				mark->freePartitionSize += flag->allocPartitionSize;
				mark->startAddr = flag->startAddr;
				fp.head = mark;
				//flag��1�����Ѻϲ�
				Flag = 1;
				break;
			}
			//��������·�������ʼ��ַ�ڵ�ǰ��������֮��
			//���·����ռ��С���뵽��ǰ����������Ȼ��ֱ�ӽ��·���ɾ��
			if (mark->freePartitionSize + mark->startAddr == flag->startAddr) {
				mark->freePartitionSize += flag->allocPartitionSize;
				//flag��1�����Ѻϲ�
				Flag = 1;
				break;
			}
			//Flag��Ϊ0���ʾû�в��뵽�����У����Խ���ŵ�����ĩβ
			if (mark->next == NULL && Flag == 0) {
				//�ڿ��з����������½�����
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

//��������
void ListOperation::endProcess(int pid)
{
	allocPartition *temp = NULL;
	processList *mark = NULL;
	allocPartition *flag;
	int errorFlag = 0;
	try {
		//ɾ������
		mark = pl.ListFind(pid);
		pl.deleteProcess(mark);
		//���ҽ��̶�Ӧ��ָ��
		temp = ap.ListFind(pid);
		//���շ���
		partitionRecyle(temp);
		//ɾ���ѷ��������Ҫ�ͷŵķ���
		ap.deleteUsedPartition(temp);
		//���з����ϲ�
		fp.freePartitionMerge();
		//��������С����
		fp.freePartitonSort();
	}
	catch (int ef) {
		throw ef;
	}
}

//�Ƿ��Զ���ʼ�½���
void ListOperation::autoStartNewProcess()
{
	int flag = 1;
	char p;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Auto start New Process" << endl;
		cout << "Staus:";
		//��0��1֮���л�
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

//��ҳ�˵�
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

//��ҳ
int ListOperation::Index()
{
	int op = -1;
	int errorFlag = 0;

	//ѭ��ֱ��return -1
	while (1) {
		errorFlag = 0;
		system("cls");
		menu();
		cout << "Input your option:" << endl;
		op = opInput();
		try {
			switch (op) {
				//��ʼ�½���
			case(1): {
				errorFlag = case1();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //ɾ������
			case(2): {
				errorFlag = case2();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //�鿴�����б�
			case(3): {
				errorFlag = case3();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //�鿴���з����б�
			case(4): {
				errorFlag = case4();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //�鿴�ѷ�������б�
			case(5): {
				errorFlag = case5();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //��ʼָ������
			case(6): {
				errorFlag = case6();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //����ָ������
			case(7): {
				errorFlag = case7();
				if (errorFlag == 0) break;
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //�Զ���ʼ�½���
			case(8): {
				errorFlag = case8();
				cout << endl;
				cout << "Press any key to back." << endl;
				getchar();
				getchar();
				break;
			}
					 //�˳�ϵͳ
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
		cout << "Please input integer number��" << endl;
		cin.clear();
		cin.ignore(2, '\n');
		cin >> op;
	}
	while (op <= 0 || op > 9) {
		cout << "Please input correct number between [0-9] :" << endl;
		cin >> op;
		while (cin.rdstate() == ios_base::failbit) {
			cout << "Please input integer number��" << endl;
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
		cout << "Please input integer number��" << endl;
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
		cout << "Please input integer number��" << endl;
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
			cout << "Please input integer number��" << endl;
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

//�����½���
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
		//����0��������
		if (pid == 0) return 0;
		processList *mark;
		int i = 0;
		try {
			//����������в����Ƿ�����ͬid�Ľ���,�����������׳�����
			//������������������д���ʹ������������������if�ж����
			mark = pl.ListFind(pid);
			//���ɹ��ҵ�������i��1
			i = 1;
			//���i��ֵΪ1�����ʾ�����б��д�����ͬid�Ľ��̣�����ѭ����������
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
			//���ز�׽��������Ϊ�պ��Ҳ������̵Ĵ�����Ϊ�������������ʾ����������û����ͬid�Ľ���
			//���Գ�����Լ���ִָ��
			if (ef == -3 || ef == -2)
				;
		}
		cout << "Input the needed Memory of Process(The max Memory is 10240KB):";
		cout << "[Enter 0 to back]" << endl;
		size = sizeInput();
		if (size == 0) return 0;
		pl.processInsert(pid, size);
		//�Զ���������
		if (ListOperation::AUTO_STARTING_PROCESS_FLAG == 1)
			startProcess(pid);
		cout << "\n" << "Add new process successful!" << endl;
		return 1;
	}
}
//ɾ������
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
		//����0��������
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

//�鿴�����б�
int ListOperation::case3()
{
	system("cls");
	menu();
	cout << "Your option: Check Process List" << endl;
	//��ӡ��������
	pl.showList();
	return 1;
}

//�鿴���з����б�
int ListOperation::case4()
{
	system("cls");
	menu();
	cout << "Your option: Check Free Partition" << endl;
	//��ӡ���з�������
	fp.showList();
	return 1;
}

//�鿴�ѷ�������б�
int ListOperation::case5()
{
	system("cls");
	menu();
	cout << "Your option: Check the Alloced Partition" << endl;
	ap.showList();
	return 1;
}

//��ʼָ������
int ListOperation::case6()
{
	int pid;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: Start Process" << endl;
		//��ʼ����
		pl.showList();
		cout << "Input the ID of Process:";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//����0��������
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

//����ָ������
int ListOperation::case7()
{
	int pid;
	while (1) {
		system("cls");
		menu();
		cout << "Your option: End Process" << endl;
		//��������
		pl.showList();
		cout << "Input the ID of Process:";
		cout << "[Enter 0 to back]" << endl;
		pid = pidInput();
		//����0��������
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

//�Զ���ʼ�½���
int ListOperation::case8()
{
	autoStartNewProcess();
	return 1;
}

//�˳�ϵͳ
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

//������з���
void ListOperation::giveFreePartition(processList *plpointer)
{
	freePartition *temp = fp.head;

	int flag = 0;
	int errorFlag = 0;
	try {
		if (temp == NULL) throw errorFlag = -2;
		//�жϷָ���ʣ�������С�Ƿ������С��Ƭ��С
		while (1) {
			//���Һ��ʵķ���
			if (temp->freePartitionSize > plpointer->needMemo) {
				//������Ƭ��С����
				//const int minPartitonSize = 50;
				//���ָ���ʣ�����������С��Ƭ����50����ʣ���С�ķ�����Ϊ�µĿ��з���
				if ((temp->freePartitionSize - plpointer->needMemo) > minPartitonSize) {
					plpointer->startAddr = temp->startAddr;
					//���ҵ����ʺϵĿ��з����Ĵ�С����ʼ��ַ�������������ķ�����С��Ϊ����
					//���طָ��ķ���ָ�룬����������С
					fp.cutFreePartition(temp->freePartitionSize, temp->startAddr, plpointer->needMemo);
					flag = 1;
				}
				//���ָ���ʣ�����С����С��Ƭ��С������ֱ�ӽ��������������̣�Ȼ�󽫸÷����ӿ��з���������ɾ��
				else if ((temp->freePartitionSize - plpointer->needMemo) <= minPartitonSize) {
					plpointer->startAddr = temp->startAddr;
					//ɾ������
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