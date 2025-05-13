#include "dataBase.h"

dataBase::dataBase() {}

// Поместить значение str в '' кавычки.
string escapeQuotes(const std::string& str) {
	return "'" + str + "'";
}

int dataBase::getLastId() {

	// Каждый раз при вызове ф-ии callback обновяется значение lastId.
	selectRecord();
	return lastId;
}

int dataBase::callback(void* data, int argc, char** argv, char** azColName) {
	// Получить массив в static ф-ии.
	auto* self = static_cast<dataBase*>(data); 
	int id;
	std::string name, text, date;

	// Каждый раз в ф-ю отправляется по одной строке, 
	for (int i = 0; i < argc; i++) {
		std::string value = argv[i] ? argv[i] : "";
		switch (i) {
		case 0: id = std::stoi(value); break;
		case 1: name = value; break;
		case 2: text = value; break;
		case 3: date = value; break;
		}
	}

	// Обьект структуры данных.
	taskValues taskVall;
	taskVall.id = id;
	taskVall.user = name;
	taskVall.text = text;
	taskVall.date = date;

	// Добавить значение в массив.
	self->tableValues.push_back(taskVall);

	// Найти наибольшее значение ID и сохранить в lastId
	for (int a = 0; a < self->tableValues.size(); a++) {
		if (id > self->lastId)
			self->lastId = id;
	}

	return 0;
}

vector <taskValues> dataBase::returnTaskValArray(int key, string name) {
	if (key == 0) {	
		// Вывести все записи
		return tableValues;
	}
	else if (key == 1) { // Вывести 10 записей
		vector <taskValues> tenTasksArr;
		for (int i = 0; i < tableValues.size(); i++) {
			if (i < 10) {
				tenTasksArr.push_back(tableValues[i]);
			}
		}

		return tenTasksArr;
	}
	else if (key == 2){ // Вывести записи под опред. ником
		vector <taskValues> usersTasks;
		for (int i = 0; i < tableValues.size(); i++) {
			if (tableValues[i].user == name) {
				usersTasks.push_back(tableValues[i]);
			}
		}

		return usersTasks;
	}
	else {
		cout << "How did you do it !?";
	}
}

bool dataBase::createObject() {
	//cout << "Create DB \n";
	db = sqlite3_open("src/dataBase/taskList.db", &DB);

	// Если в БД таблицы нет - создать.
	if (selectRecord()) {
		createDB();
		cout << "Created new DB." << endl;
	}
	else {
		cout << "DB opened." << endl;
	}

	return db;
}

bool dataBase::createDB() {
	// Запрос на создание таблицы.
	string request = "CREATE TABLE taskList("
					"ID	INT PRIMARY KEY NOT NULL,"
					"UserName	TEXT,"
					"taskText	TEXT,"
					"date	TEXT );";

	runSQLRequest(request);
}

bool dataBase::crateRecord(int id, string userN, string text, string date) {
	stringstream req;

	// Запрос на создание записи в БД.
	req << "INSERT INTO taskList (ID, UserName, taskText, date) VALUES ("
		<< id << " ,"
		<< escapeQuotes(userN) << " ,"
		<< escapeQuotes(text) << " ,"
		<< escapeQuotes(date) << ");";

	//cout << "req:" << req.str();
	string request = req.str();

	runSQLRequest(request);
	
	return 0;
}

// Вывести данные из БД
bool dataBase::selectRecord() {
	tableValues.clear();

	// Запрос на вывод всех записей из БД.
	string req = "SELECT * FROM taskList";

	char* errorMessage;
	db = sqlite3_exec(DB, req.c_str(), dataBase::callback, this, &errorMessage);

	if (db != SQLITE_OK) {
		cout << "SELECT Error ! " << endl;
		cout << errorMessage << endl;
		return 1;
	}
	else {
		//cout << "Request worked success !" << endl;
		return 0;
	}

	return 0;
}

bool dataBase::updateRecord(int id, string val) {
	stringstream req;
	
	// Запрос на обновление записи в БД по ключу.
	req << "UPDATE taskList WHERE ID = " << id << " SET taskText = " << val << ";";

	string request = req.str();
	runSQLRequest(request);

	return 0;
}

bool dataBase::deleteRecord(int id) {
	for (int i = 0; i < tableValues.size(); i++) {
		if (tableValues[i].id == id) {
			stringstream req;
			// Запрос на удаление записи из БД по ключу.
			req << "DELETE FROM taskList WHERE ID = " << id << ";";

			string request = req.str();

			runSQLRequest(request);
		}
	}

	return 0;
}

// Функция для выполнения SQL запроса.
bool dataBase::runSQLRequest(string req) {
	char* errorMessage;

	// Выполнение запроса.
	// DB - обращение к открытой БД.
	// req - SQL запрос.
	// NULL - Куда отправляется полученное значение ( если есть )
	// 0 - значение отправляемое в callback.
	// errorMessage - в данную переменную отправляется ошибка если таковая есть.
	db = sqlite3_exec(DB, req.c_str(), NULL, 0, &errorMessage);

	// Обработка ошибки, если есть ошибка - вывести сообщение в консоль.
	if (db != SQLITE_OK) {
		cout << "SQL request Error !" << endl;
		cout << errorMessage << endl;
		return 1;
	}
	else {
		//cout << "Request worked success !" << endl;
		return 0;
	}
}