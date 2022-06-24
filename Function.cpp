#include "Function.h"


vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

void PrintHelp()
{
    cout << "Команды:" << endl;
    cout << "init" << endl;
    cout << "help" << endl;
    cout << "exit" << endl;
    cout << "CreateUser" << endl;
    cout << "CreateFile" << endl;
    cout << "ReadFile" << endl;
    cout << "WriteFile" << endl;
    cout << "AddPerm" << endl;
    cout << "DelPerm" << endl;
    cout << "DelFile" << endl;
    cout << "DelUser" << endl;
}
