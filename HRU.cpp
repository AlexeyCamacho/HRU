#include <iostream>
#include <string>
#include "ModelHRU.h"

using namespace std;

string input = "";

ModelHRU model;

int main()
{
	setlocale(LC_ALL, "rus");

	PrintHelp();

    while (1) {
		cin >> input;

		if (input == "exit") {
			model.save();
			break;
		}
		else if (input == "init") {
			if (model.GetSizeUsers() == 0) {
				string login;
				cout << "Введите логин начального пользователя." << endl;
				cin >> input;
				login = input;
				cout << "Введите пароль начального пользователя." << endl;
				cin >> input;
				if (model.CreateUser(login, input)) {
					cout << "Пользователь создан." << endl;
				}
				else {
					cout << "Пользователь с таким логином уже существует." << endl;
				}
				
			}
			else {
				cout << "В системе уже есть пользователи." << endl;
			}
		}
		else if (input == "help") {
			PrintHelp();
		}
		else if (input == "CreateUser") {
			string login;

			if (model.CheckUser()) {

				cout << "Введите логин нового пользователя." << endl;
				cin >> input;
				login = input;
				cout << "Введите пароль нового пользователя." << endl;
				cin >> input;

				if (model.CreateUser(login, input)) {
					cout << "Пользователь создан." << endl;
				}
				else {
					cout << "Пользователь с таким логином уже существует." << endl;
				}
			}
			else {
				cout << "Неверный логин или пароль." << endl;
			}
		} 
		else if (input == "CreateFile") {
			string login, password;
			cout << "Введите ваш логин." << endl;
			cin >> login;
			cout << "Введите ваш пароль." << endl;
			cin >> password;

			if (model.CheckUser(login, password)) {
				string file, text;
				cout << "Введите имя файла." << endl;
				cin >> file;
				cout << "Введите текст." << endl;
				cin >> text;

				if (model.CreateFile(file, text)) {
					cout << "Файл создан." << endl;
				}
				else {
					cout << "Файл с таким именем уже существует." << endl;
				}
			}
		}
    }

	return 0;
}

