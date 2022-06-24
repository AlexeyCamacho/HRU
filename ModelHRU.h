#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "MD5.h"
#include "Function.h"

using namespace std;

class ModelHRU
{
private:
	vector<vector<int>> accessMatrix;
	vector<pair<string, string>> users;
	vector<string> files;
public:
	ModelHRU();
	void save();
	int GetSizeUsers();
	int GetPermission(string login, string file);
	int SetPermission(string login, string file, string flag);
	int DelPermission(string login, string file, string flag);
	int CreateUser(string login, string password);
	int DeleteUser(string login);
	string Authentication();
	int CreateFile(string name, string text);
	int DeleteFile(string name);
	int WriteFile(string name, string text);
	void ReadFile(string name);
	int CheckUser(string login);
};

