#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ModelHRU
{
private:
	vector<vector<int>> accessMatrix;
	vector<string> objects;
	vector<string> files;
public:
	ModelHRU();
	void save();
	int GetPermission(int i, int j);
	int SetPermission(int i, int j);
	int CreateUser(string login, string password);
	int DeleteUser(string login);
	int CheckUser(string login, string password);
	int CreateFile(string name, string text);
	int DeleteFile(string name);
	int WriteFile(string name, string text);
	string ReadFile(string name);
};

