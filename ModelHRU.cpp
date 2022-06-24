#include "ModelHRU.h"

ModelHRU::ModelHRU()
{

    int result;
    result = _mkdir("model");

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
        while (getline(matrixFile, input)) {
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
    ofstream usersFile("model/users.txt");
    vector<pair<string, string>>::iterator itUsers;

    for (itUsers = users.begin(); itUsers != users.end(); itUsers++) {
        usersFile << (*itUsers).first << ";" << (*itUsers).second << endl;
    }

    usersFile.close();

    ofstream filesFile("model/files.txt");
    vector<string>::iterator itFiles;

    for (itFiles = files.begin(); itFiles != files.end(); itFiles++) {
        filesFile << *itFiles << endl;
    }

    filesFile.close();

    ofstream matrixFile("model/matrix.txt");
    vector<vector<int>>::iterator itMatrix;
    vector<int>::iterator itMatrixJ;

    for (itMatrix = accessMatrix.begin(); itMatrix != accessMatrix.end(); itMatrix++) {
        for (itMatrixJ = (*itMatrix).begin(); itMatrixJ != (*itMatrix).end(); itMatrixJ++) {
            matrixFile << *itMatrixJ;
            if (itMatrixJ != (*itMatrix).end()--) {
                matrixFile << ";";
            }
        }
        matrixFile << endl;
    }

    matrixFile.close();
}

int ModelHRU::GetSizeUsers()
{
    return this->users.size();
}

int ModelHRU::GetPermission(string login, string file)
{
    int i, j;
    vector<string>::iterator it = find(files.begin(), files.end(), file);

    if (it == files.end()) {
        return -1;
    }

    i = distance(files.begin(), it);

    auto it1 = find_if(users.begin(), users.end(), [login](pair<string, string>& current) { return current.first == login; });
    j = distance(users.begin(), it1);

    return accessMatrix[i][j];
}

int ModelHRU::SetPermission(string login, string file, string flag)
{
    if (flag != "r" && flag != "w" && flag != "o") {
        return 0;
    }

    int i, j;
    vector<string>::iterator it = find(files.begin(), files.end(), file);
    i = distance(files.begin(), it);

    auto it1 = find_if(users.begin(), users.end(), [login](pair<string, string>& current) { return current.first == login; });
    j = distance(users.begin(), it1);

    int perm = accessMatrix[i][j];
    
    if (flag == "r") {
        perm |= 4;
    }
    else if (flag == "w") {
        perm |= 2;
    }
    else {
        perm |= 1;
    }

    accessMatrix[i][j] = perm;

    return 1;
}

int ModelHRU::DelPermission(string login, string file, string flag)
{
    if (flag != "r" && flag != "w" && flag != "o") {
        return 0;
    }

    int i, j;
    vector<string>::iterator it = find(files.begin(), files.end(), file);
    i = distance(files.begin(), it);

    auto it1 = find_if(users.begin(), users.end(), [login](pair<string, string>& current) { return current.first == login; });
    j = distance(users.begin(), it1);

    int perm = accessMatrix[i][j];

    if (flag == "r") {
        perm &= 3;
    }
    else if (flag == "w") {
        perm &= 5;
    }
    else {
        perm &= 6;
    }

    accessMatrix[i][j] = perm;

    return 1;
}

int ModelHRU::CreateUser(string login, string password)
{
    string hachPassword{ md5(password) };
    vector<pair<string, string>>::iterator it = find(users.begin(), users.end(), make_pair(login, hachPassword));
    if (it == users.end()) {
        users.push_back(make_pair(login, hachPassword));
    }
    else {
        return 0;
    }
    
    vector<vector<int>>::iterator it1;
    for (it1 = accessMatrix.begin(); it1 != accessMatrix.end(); it1++) {
        (* it1).push_back(0);
    }

    return 1;
}

int ModelHRU::DeleteUser(string login)
{
    int j;
    auto it = find_if(users.begin(), users.end(), [login](pair<string, string>& current) { return current.first == login; });
    j = distance(users.begin(), it);
    users.erase(it);

    for (int i = 0; i < accessMatrix.size(); i++) {
        accessMatrix[i].erase(accessMatrix[i].begin() + j);
    }

    return 1;
}

string ModelHRU::Authentication()
{
    string login, password;
    cout << "Введите ваш логин." << endl;
    cin >> login;
    cout << "Введите ваш пароль." << endl;
    cin >> password;

    string hachPassword{ md5(password) };
    vector<pair<string, string>>::iterator it = find(users.begin(), users.end(), make_pair(login, hachPassword));
    if (it != users.end()) {
        return login;
    }
    else {
        cout << "Неверный логин или пароль." << endl;
        return "";
    }
}

int ModelHRU::CreateFile(string name, string text)
{
    vector<string>::iterator it = find(files.begin(), files.end(), name);
    if (it == files.end()) {
        files.push_back(name);
    }
    else {
        return 0;
    }

    int n = users.size();

    accessMatrix.push_back(vector<int> (n, 0));

    string nameFile = "model/" + name;
    ofstream file(nameFile);

    file << text;

    file.close();

    return 1;
}

int ModelHRU::DeleteFile(string name)
{
    int i;
    vector<string>::iterator it = find(files.begin(), files.end(), name);
    i = distance(files.begin(), it);
    files.erase(it);
    accessMatrix.erase(accessMatrix.begin() + i);

    return 1;
}

int ModelHRU::WriteFile(string name, string text)
{
    string nameFile = "model/" + name;
    ofstream file(nameFile, ios::app);
    if (!file.is_open()) return -1;
    file << text << endl;
    file.close();
    return 1;
}

void ModelHRU::ReadFile(string name)
{
    string input;
    string nameFile = "model/" + name;
    ifstream file(nameFile);
    if (file.is_open()) {
        while (getline(file, input)) {
            cout << input << endl;
        }
    }

    file.close();
}

int ModelHRU::CheckUser(string login)
{
    auto it1 = find_if(users.begin(), users.end(), [login](pair<string, string>& current) { return current.first == login; });
    if (it1 != users.end()) {
        return 1;
    }
    else {
        return 0;
    }
}
