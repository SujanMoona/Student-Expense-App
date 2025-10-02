#include<iostream>
#include<fstream>
#include<string>

using namespace std;

/*// Read from the text file
ifstream MyReadFile("filename.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, myText)) {
  // Output the text from the file
  cout << myText;
}*/
struct User{
    string user_name;
    string password;
};

class account{
    string user_name;
    string uname, pass;
    

public:
void login(){
    cout<<"Enter username:";
    cin>>uname;
    cout<<"Enter password:";
    cin>>pass;
}

void createFile(){
 cout<<"Enter username: ";
 cin>>user_name;
 user_name=user_name+".txt";
 ofstream file(user_name);
 file<<user_name;
 file.close();
}



bool findUser(){
 User u;
 
 ifstream User_info("users.txt");// to read the file of user and password
 login();//user input
 
 while (User_info>>u.user_name >> u.password){ 
    if ( uname == u.user_name && pass == u.password ){
       return true;   
    }
 }
 return false;
 
}

void account_main(){
    login();
    

}


};



int main(){

return 0;

 
}

