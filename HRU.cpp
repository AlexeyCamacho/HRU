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
			string login = model.Authentication();

			if (login != "") {

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
		}
		else if (input == "CreateFile") {
			string login = model.Authentication();

			if (login != "") {
				string file, text;
				cout << "Введите имя файла." << endl;
				cin >> file;
				cout << "Введите текст." << endl;
				cin >> text;

				if (model.CreateFile(file, text)) {
					model.SetPermission(login, file, "r");
					model.SetPermission(login, file, "w");
					model.SetPermission(login, file, "o");
					cout << "Файл создан." << endl;
				}
				else {
					cout << "Файл с таким именем уже существует." << endl;
				}
			}
		}
		else if (input == "ReadFile") {
			string login = model.Authentication();

			if (login != "") {
				string file;
				cout << "Введите имя файла." << endl;
				cin >> file;

				int perm = model.GetPermission(login, file);
				if (perm >= 0) {
					if (perm & (1 << 2)) {
						model.ReadFile(file);
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Файл не найден." << endl;
				}
			}
		}
		else if (input == "WriteFile") {
			string login = model.Authentication();

			if (login != "") {
				string file, text;
				cout << "Введите имя файла." << endl;
				cin >> file;

				int perm = model.GetPermission(login, file);
				if (perm >= 0) {
					if (perm & (1 << 1)) {
						cout << "Введите текст." << endl;
						cin >> text;
						model.WriteFile(file, text);
						cout << "Успешно." << endl;
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Файл не найден." << endl;
				}
			}
		}
		else if (input == "AddPerm") {
			string login = model.Authentication();

			if (login != "") {
				string file, flag, otherUser;
				cout << "Введите имя файла для выдачи прав." << endl;
				cin >> file;
				cout << "Введите право (r, w, o)." << endl;
				cin >> flag;
				cout << "Введите пользователя для выдачи прав." << endl;
				cin >> otherUser;

				int perm = model.GetPermission(login, file);
				if (perm >= 0) {
					if (perm & 1) {
						if (model.CheckUser(otherUser)) {
							if (model.SetPermission(otherUser, file, flag)) { cout << "Успешно." << endl; }
							else { cout << "Неверный флаг." << endl; }
						}
						else {
							cout << "Пользователь не найден." << endl;
						}
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Файл не найден." << endl;
				}
			}
		}
		else if (input == "DelPerm") {
			string login = model.Authentication();

			if (login != "") {
				string file, flag, otherUser;
				cout << "Введите имя файла для удаления прав." << endl;
				cin >> file;
				cout << "Введите право (r, w, o)." << endl;
				cin >> flag;
				cout << "Введите пользователя для удаления прав." << endl;
				cin >> otherUser;

				int perm = model.GetPermission(login, file);
				if (perm >= 0) {
					if (perm & 1) {
						if (model.CheckUser(otherUser)) {
							if (model.DelPermission(otherUser, file, flag)) { cout << "Успешно." << endl; }
							else { cout << "Неверный флаг." << endl; }
						}
						else {
							cout << "Пользователь не найден." << endl;
						}
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Файл не найден." << endl;
				}
			}
		}
		else if (input == "DelFile") {
			string login = model.Authentication();

			if (login != "") {
				string file;
				cout << "Введите имя файла для удаления." << endl;
				cin >> file;

				int perm = model.GetPermission(login, file);
				if (perm >= 0) {
					if (perm & 1) {
						if(model.DeleteFile(file)) { cout << "Файл удалён." << endl; }
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Файл не найден." << endl;
				}
			}
		}
		else {
			cout << "Неверная команда." << endl;
		}

		model.save();
	}

	return 0;
}

