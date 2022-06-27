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
					model.SetPermission(login, login, "r", false);
					model.SetPermission(login, login, "w", false);
					model.SetPermission(login, login, "o", false);
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
				string otherLogin = input;
				cout << "Введите пароль нового пользователя." << endl;
				cin >> input;

				if (model.CreateUser(otherLogin, input)) {
					model.SetPermission(otherLogin, otherLogin, "r", false);
					model.SetPermission(otherLogin, otherLogin, "w", false);
					model.SetPermission(otherLogin, otherLogin, "o", false);
					model.SetPermission(login, otherLogin, "r", false);
					model.SetPermission(login, otherLogin, "w", false);
					model.SetPermission(login, otherLogin, "o", false);
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
					model.SetPermission(login, file, "r", true);
					model.SetPermission(login, file, "w", true);
					model.SetPermission(login, file, "o", true);
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

				if (model.CheckFile(file)) {
					int perm = model.GetPermission(login, file, true);
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

				if (model.CheckFile(file)) {
					int perm = model.GetPermission(login, file, true);
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
				string object, flag, otherUser;
				bool isFile = false;
				cout << "Выдать права на файл или на пользователя? (user/file)" << endl;
				cin >> object;

				if (object == "file") {
					isFile = true;
				}

				cout << "Введите имя файла/пользователя (объект) для выдачи прав." << endl;
				cin >> object;
				cout << "Введите право (r, w, o)." << endl;
				cin >> flag;
				cout << "Введите пользователя (субъект) для выдачи прав." << endl;
				cin >> otherUser;

				if ((!isFile && model.CheckUser(object)) || (isFile && model.CheckFile(object))) {
					int perm = model.GetPermission(login, object, isFile);
					if (perm & 1) {
						if (model.CheckUser(otherUser)) {
							if (model.SetPermission(otherUser, object, flag, isFile)) { cout << "Успешно." << endl; }
							else { cout << "Неверный флаг." << endl; }
						}
						else {
							cout << "Субъект не найден." << endl;
						}
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Объект не найден." << endl;
				}
			}
		}
		else if (input == "DelPerm") {
			string login = model.Authentication();

			if (login != "") {
				string object, flag, otherUser;
				bool isFile = false;
				cout << "Удалить права на файл или на пользователя? (user/file)" << endl;
				cin >> object;

				if (object == "file") {
					isFile = true;
				}

				cout << "Введите имя файла/пользователя (объект) для удаления прав." << endl;
				cin >> object;
				cout << "Введите право (r, w, o)." << endl;
				cin >> flag;
				cout << "Введите пользователя (субъект) для удаления прав." << endl;
				cin >> otherUser;

				if ((!isFile && model.CheckUser(object)) || (isFile && model.CheckFile(object))) {
					int perm = model.GetPermission(login, object, isFile);
					if (perm & 1) {
						if (model.CheckUser(otherUser)) {
							if (model.DelPermission(otherUser, object, flag, isFile)) { cout << "Успешно." << endl; }
							else { cout << "Неверный флаг." << endl; }
						}
						else {
							cout << "Субъект не найден." << endl;
						}
					}
					else {
						cout << "Недостаточно прав." << endl;
					}
				}
				else {
					cout << "Объект не найден." << endl;
				}
			}
		}
		else if (input == "DelFile") {
			string login = model.Authentication();

			if (login != "") {
				string file;
				cout << "Введите имя файла для удаления." << endl;
				cin >> file;

				if (model.CheckFile(file)) {
					int perm = model.GetPermission(login, file, true);
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
		else if (input == "DelUser") {
		string login = model.Authentication();

		if (login != "") {
			string otherUser;
			cout << "Введите логин пользователя для удаления." << endl;
			cin >> otherUser;
			if (model.CheckUser(otherUser)) {
				int perm = model.GetPermission(login, otherUser, false);
				if (perm & 1) {
					if (model.DeleteUser(otherUser)) { cout << "Пользователь удалён." << endl; }
				}
				else {
					cout << "Недостаточно прав." << endl;
				}	
			} 
			else {
				cout << "Пользователь не найден." << endl;
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

