#pragma once
//#include <iostream>
#include <vector>
#include "./dataBase/dataBase.h"

using namespace std;

class TaskManager
{
private:
	dataBase* db; // ������ �� ��� ��������� � ����.
	
public:
	TaskManager();
	// ���������� ��������� ID � ��
	int getLastId();

	// ������� ������ 
	bool crateTask(taskValues taskVal);

	// �������� ��� ������
	bool showTaskList();

	// �������� 10 �����
	bool showTenTasks();

	// �������� ������ �����. ������������
	bool showUsersTaskList(string usN);

	// �������� ������
	bool editTask(int id, string val);

	// ������� ������
	bool deleteTask(int id);
};

