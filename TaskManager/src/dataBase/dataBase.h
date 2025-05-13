#pragma once
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
	
// Структура с макетом для данных из БД.
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

	// Получить самый большой IP
	int getLastId();

	bool createObject();

	// Создать БД
	bool createDB();

	// Создать запись в БД
	bool crateRecord(int id, string userN, string text, string date);

	// Вывести запись из БД
	bool selectRecord();

	// Обносить запись в БД
	bool updateRecord(int id, string val);

	// Удалить запись из БД
	bool deleteRecord(int id);

	// Вывести записи.
	vector <taskValues> returnTaskValArray(int key = 0, string name = "");

private:
	// Получение данных ответа из SQL запроса.
	static int callback(void* data, int argc, char** argv, char** azColName);

	// В данной переменной сохраняется ID последней записн.
	int lastId = 0;	

	// Массив со значениями из БД.
	vector <taskValues> tableValues;
	
	// Выполнить SQL запрос.
	bool runSQLRequest(string req);
	int db = 0;
};

