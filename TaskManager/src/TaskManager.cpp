#include "TaskManager.h"

TaskManager::TaskManager() {
	db = new dataBase();

	// �������/������� ��.
	db->createObject();
}

// �������� ��������� Id �� ��.
int TaskManager::getLastId() {
	return db->getLastId();;
}

bool TaskManager::crateTask(taskValues taskValue) {
	//cout << "Create task" << taskValue.text << taskValue.user << taskValue.date << endl;
	db->crateRecord(taskValue.id, taskValue.user, taskValue.text, taskValue.date);

	return 0;
}

bool TaskManager::showTaskList() {
	cout << "Show task list" << endl;
	
	// �������� ��� ������.
	db->selectRecord();

	// ��������� ������ � ������, ���� 0 ������� ��� ������.
	vector <taskValues> values = db->returnTaskValArray(0);

	// ������� ������ �� ������� �� ������.
	for (int i = 0; i < values.size(); i++) {
		cout << "<Start ------------------>" << endl;
		cout << "Task list record #" << i + 1 << endl;
		cout << "Id: " << values[i].id << endl;
		cout << "User name: " << values[i].user << endl;
		cout << "Text: " << values[i].text << endl;
		cout << "Date: " << values[i].date << endl;
		cout << "<End ------------------> \n" << endl;
	}

	return 0;
}

bool TaskManager::showTenTasks() {
	cout << "Show 10 tasks....." << endl;
	db->selectRecord();

	// ��������� ������ � ������, ���� 1 ������� 10 �������.
	vector <taskValues> values = db->returnTaskValArray(1);

	for (int i = 0; i < values.size(); i++) {
		cout << "<Start ------------------>" << endl;
		cout << "Task list resord #" << i + 1 << endl;
		cout << "Id: " << values[i].id << endl;
		cout << "User name: " << values[i].user << endl;
		cout << "Text: " << values[i].text << endl;
		cout << "Date: " << values[i].date << endl;
		cout << "<End ------------------/> \n" << endl;
	}

	return 0;
}

bool TaskManager::showUsersTaskList(string userName) {
	cout << "Show User's task ----> " << userName << endl;
	db->selectRecord();

	// ��������� ������ � ������, ���� 2 ������� ������ ���������� ������������.
	vector <taskValues> values = db->returnTaskValArray(2, userName);

	for (int i = 0; i < values.size(); i++) {
		cout << "<Start ------------------>" << endl;
		cout << "Task list record #" << i + 1 << endl;
		cout << "Id: " << values[i].id << endl;
		cout << "User name: " << values[i].user << endl;
		cout << "Text: " << values[i].text << endl;
		cout << "Date: " << values[i].date << endl;
		cout << "<End ------------------/> \n" << endl;
	}

	return 0;
}

bool TaskManager::editTask(int id, string val) {
	cout << "Edit task" << id << val << endl;
	db->updateRecord(id, val);

	return 0;
}

bool TaskManager::deleteTask(int id) {
	cout << "Delete task" << id << endl;
	db->deleteRecord(id);

	return 0;
}


