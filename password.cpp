#include<iostream>
#include <fstream>
#include<sstream>
#include <functional> // hash function 
#include <string>

using namespace std;

int main(){

    string hashPassword(const string &s){
    hash<string> h;
    ostringstream ss;
    ss << h(s);
    return ss.str();
}

void findPassword(){
    ifstream file("users.txt");
    string line;
    while (getline(file, line)){
        size_t pos = line.find(',');// Find position of ,
        if (pos == string::npos) continue; // If there is no comma in line , move to next line
        string storedUser = line.substr(0, pos);
        string storedHash = line.substr(pos +1);
        if (storedUser == username && storedHash == hashed){
            cout<< "Login successful - Welcome "<< username << "!\n";
        }
    }
}


bool userExists(const string &username) {// Use when the username already exist in signup
    ifstream f("users.txt");
    string line;
    while (getline(f, line)) {
        size_t pos = line.find(','); 
        if (pos != string::npos) {
            if (line.substr(0, pos) == username) return true;
        }
    }
    return false;
}
return 0;
}
