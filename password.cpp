#include<iostream>
#include <fstream>
#include<sstream> 
#include <string>
#include <openssl/sha.h>  // For SHA-256 hashing

using namespace std;

int main(){

string sha256(const string &str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str.c_str(), str.size(), hash);
    ostringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    return ss.str();
}
 
   
/*To Find password*/ 

/* while (getline(file, line)){
        size_t pos = line.find(',');// Find position of ,
        if (pos == string::npos) continue; // If there is no comma in line , move to next line
        string storedUser = line.substr(0, pos);
        string storedHash = line.substr(pos +1);
        if (storedUser == username && storedHash == hashed){
            cout<< "Login successful - Welcome "<< username << "!\n";
        }
    }*/

string findPassword(string inputPassword){// Take input from user
    
}


return 0;
}
