#include "TaskManager.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    TaskManager *tm = new TaskManager();

    int command = 0;

    do {
        int lastId = tm->getLastId() + 1;
        cout << "lastId: " << lastId << endl;
        cout << "--------------------------- \n";
        cout << "1: Create task \n";
        cout << "2: Edit task (find with ID) \n";
        cout << "3: Delete task \n";
        cout << "4: Show all task lisk \n";
        cout << "5: Show User's task list \n";
        cout << "0: Exit \n";
        cout << "---------------------------\n";

        cin >> command;

        string text;
        string userName;
        string date;

        taskValues task_val;
        int taskNum = 0;

        // пользователь ввел команду - определить какое действие выполнить.
        switch (command) {
        case 1:
            // В данной переменной сохраняется последний ID в БД.
            task_val.id = lastId;

            cout << "Write values:  \n";
            cout << "User name:  \n";
            cin.ignore();
            getline(cin, userName);
            task_val.user = userName;

            cout << "Task:  \n";
            cin.ignore();
            getline(cin, text);
            task_val.text = text;

            cout << "Date - dd:mm:yy:  \n";
            getline(cin, date);
            task_val.date = date;

            // Создать запись.
            tm->crateTask(task_val);
            break;
        case 2:
            tm->showTaskList();
            cout << "I show you last 10 tasks, find ID for edit and write at first val at unswer. \n";
            cout << "Write ID: ";
            cin >> lastId;

            cout << "Write text: ";
            cin >> text;

            // Изменить запись.
            tm->editTask(lastId, text);
            break;
        case 3:
            // показать 10 записей.
            tm->showTenTasks();

            cout << "I show you last 10 tasks, find ID task where you want delete. \n";
            cout << "If you want see all tasks - write 011 \n";
            cout << "Write ID: ";
            cin >> taskNum;

            if (taskNum == 011) { // Если нужно больше 10ти - вывести все.
                bool shTask = tm->showTaskList();
            }
            else { // Удалить запись по ID.
                bool delTask = tm->deleteTask(taskNum);
                break;
            }

            cout << "You see all task list, find task where you want to delete and write ID. \n";
            cout << "Write ID: ";
            cin >> taskNum;
            tm->deleteTask(taskNum); // Удалить запись по ID.
            break;

        case 4:
            // Показать весь список задач.
            tm->showTaskList();
            break;
        case 5:
            cout << "Write User name: ";
            cin.ignore();
            getline(cin, userName);
            // Показать задачи определенного пользователя.
            tm->showUsersTaskList(userName);
            break;
        case 0:           
            cout << "Entered EXIT Command !";
            break;
        default:
            cout << "Incorrect symbol ! \n";
            break;
        }
    } while (command != 0); // Если ввели 0 - завершить работу.
}