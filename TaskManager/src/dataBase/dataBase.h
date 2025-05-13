#pragma once
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
	
// ��������� � ������� ��� ������ �� ��.
struct taskValues {
	int id = 0;
	string text;
	string user;
	string date;
};

class dataBase
{
public:
	dataBase();
	sqlite3* DB;

	// �������� ����� ������� IP
	int getLastId();

	bool createObject();

	// ������� ��
	bool createDB();

	// ������� ������ � ��
	bool crateRecord(int id, string userN, string text, string date);

	// ������� ������ �� ��
	bool selectRecord();

	// �������� ������ � ��
	bool updateRecord(int id, string val);

	// ������� ������ �� ��
	bool deleteRecord(int id);

	// ������� ������.
	vector <taskValues> returnTaskValArray(int key = 0, string name = "");

private:
	// ��������� ������ ������ �� SQL �������.
	static int callback(void* data, int argc, char** argv, char** azColName);

	// � ������ ���������� ����������� ID ��������� ������.
	int lastId = 0;	

	// ������ �� ���������� �� ��.
	vector <taskValues> tableValues;
	
	// ��������� SQL ������.
	bool runSQLRequest(string req);
	int db = 0;
};

