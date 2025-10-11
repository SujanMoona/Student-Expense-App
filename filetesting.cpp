#include<iostream>
#include<fstream>
#include<conio.h>
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
    string username;
    string password;
};

class account{
    string user_name,password;
    string uname, pass;
     User u;
     bool signup=false,l=false;
     bool user_exist=false;
    

public:

//this is main funtion of the account login or signup
void login_menu(){
   
    int choice=0;
    while(true){
        system("cls");// this clears the terminal
        cout<<(choice==0?">>" :" ")<<"Login"<<endl;  
        cout<<(choice==1?">>" :" ")<<"Signup"<<endl;
    

        char key=_getch();
        if(key==72){
                choice=(choice+1)%2; 
        }else if(key==80){
                choice=(choice+1)%2;
        }else if(key==13){
                break;
        }

    }
    switch(choice+1){
          
        case 1:{
            system("cls");
            login();
            l=findUser();
            if(findUser()){
                cout<<"welcome "<<u.username<<endl;
                u.username=u.username+".txt";
                ofstream file(u.username,ios ::in | ios::out);//to read or write accordin to (<< ,>>);
        //now this can alloe you to store and write the daily expenses 
            }
            else{
                cout<<"user name not found!"<<endl;
                login_menu();
            }
            break;
        }
        case 2:{
                system("cls");
                create_file();
            
            break;
        }
    }


    if(signup || l){
    cout<<(l? "login succesful":"signup succesful")<<endl;
        
    }

  

}
void login(){
    cout<<"Enter username:";
    cin>>uname;
    cout<<"Enter password:";
    cin>>pass;
}

void create_file(){
 cout<<"Enter username: ";
 cin>>user_name;
 ifstream User_info("users.txt");// to read the file of user and password
 while (User_info>>u.username >> u.password){ 
    //to avoid duplicate username;
      if(user_name==u.username){
        cout<<"user already exist"<<endl;
        login_menu();
    }
}
    User_info.close();
    cout<<"Enter password: ";
    cin>>password;

 //user_name=user_name+".txt";
 ofstream file(user_name+".txt");
 file<<user_name;
 file.close();

 ofstream file1("users.txt",ios::app );
 file1<<user_name<<" "<<password<<endl;
 file1.close();
 
 cout<<"signup Successful!"<<endl;

}


//to findout is the user exist or not

bool findUser(){

 ifstream User_info("users.txt");// to read the file of user and password

 
 while (User_info>>u.username >> u.password){ 
    //to avoid duplicate username;
<<<<<<< Updated upstream
      if(uname==u.username && pass!=u.password){
     
       user_exist=true;
    } 
     if ( uname == u.username && pass == u.password ){
=======
     if ( uname == u.user_name && pass == u.password ){
>>>>>>> Stashed changes
       return true;   
    }
  
 }
 return false;
 User_info.close();
 
}
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
};



int main(){
account a;
a.login_menu();
return 0;
}

