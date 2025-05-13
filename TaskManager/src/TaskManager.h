#pragma once
//#include <iostream>
#include <vector>
#include "./dataBase/dataBase.h"

using namespace std;

class TaskManager
{
private:
	dataBase* db; // Обьект БД для обращения к нему.
	
public:
	TaskManager();
	// Возвращает последний ID в БД
	int getLastId();

	// Создать задачу 
	bool crateTask(taskValues taskVal);

	// Показать все задачи
	bool showTaskList();

	// Показать 10 задач
	bool showTenTasks();

	// Показать задачи опред. пользователя
	bool showUsersTaskList(string usN);

	// Измерить задачу
	bool editTask(int id, string val);

	// Удалить задачу
	bool deleteTask(int id);
};

