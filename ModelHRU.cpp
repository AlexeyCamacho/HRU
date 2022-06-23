#include "ModelHRU.h"

ModelHRU::ModelHRU()
{
    string input;
	ifstream usersFile("model/users.txt");
    if (usersFile.is_open()) {
        while (getline(usersFile, input)) {
            vector<string> line = split(input, ';');
            users.push_back(make_pair(line[0], line[1]));
        }
    }
    else {
        ofstream usersFile("model/users.txt");
    }

    usersFile.close();

    ifstream filesFile("model/files.txt");
    if (filesFile.is_open()) {
        while (getline(filesFile, input)) {
            files.push_back(input);
        }
    }
    else {
        ofstream filesFile("model/files.txt");
    }

    filesFile.close();

    ifstream matrixFile("model/matrix.txt");
    if (matrixFile.is_open()) {
        while (getline(filesFile, input)) {
            vector<string> line = split(input, ';');
            vector<int> intLine;
            for (vector<string>::iterator iter = line.begin(); iter != line.end(); iter++) {
                intLine.push_back(stoi(*iter));
            }
            accessMatrix.push_back(intLine);
        }
    }
    else {
        ofstream matrixFile("model/matrix.txt");
    }

    matrixFile.close();

}

void ModelHRU::save()
{
}

int ModelHRU::GetSizeUsers()
{
    return this->users.size();
}

int ModelHRU::CreateUser(string login, string password)
{
    string hachPassword{ md5(password) };
    vector<pair<string, string>>::iterator it = find(users.begin(), users.end(), make_pair(login, hachPassword));
    if (it == users.end()) {
        users.push_back(make_pair(login, hachPassword));
        return 1;
    }
    else {
        return 0;
    }
}

int ModelHRU::CheckUser(string login, string password)
{
    string hachPassword{ md5(password) };
    vector<pair<string, string>>::iterator it = find(users.begin(), users.end(), make_pair(login, hachPassword));
    if (it != users.end()) {
        return 1;
    }
    else {
        return 0;
    }
}
