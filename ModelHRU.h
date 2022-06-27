#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <cstdio>
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
	int GetPermission(string login, string file, bool isFile);
	int SetPermission(string login, string file, string flag, bool isFile);
	int DelPermission(string login, string file, string flag, bool isFile);
	int CreateUser(string login, string password);
	int DeleteUser(string login);
	string Authentication();
	int CreateFile(string name, string text);
	int DeleteFile(string name);
	int WriteFile(string name, string text);
	void ReadFile(string name);
	int CheckUser(string login);
	int CheckFile(string file);
};

