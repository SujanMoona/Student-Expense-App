#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include <windows.h> //for use sleep(time in milisec) this is the funtion to delay the run


using namespace std;

struct User{
    string username;
    string password;
};

class account{
 
public:
struct User user;// to use the username globally;
struct User user_file;// varible for use in file checking;
void login_menu(){
   
    int choice=0;
    while(true){
        system("cls");
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
                cout<<"welcome "<<u.user_name<<endl;
                u.user_name=u.user_name+".txt";
                ofstream file(u.user_name,ios ::in | ios::out);//to read or write accordin to (<< ,>>);
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
    bool user_exist=false;
    cout<<"Enter username:";
    cin>>user.username;



 ifstream User_info("users.txt");// to read the file of user and password
 while (User_info>>user_file.user_name >> user_file.password){ 
    //to avoid duplicate username;
      if(user.username==user_file.user_name){
        user_exist=true;
      break;// it means user is  exist;
      }
 }
 if(!user_exist){
  cout<<"user not found! try again"<<endl;
  
  sleep(2000);//to dealy the call login menu call bu 2000 milisecond i.e 2 sec;
  login_menu();
 }
 //run until password is correct ..(we can also thinking about adding forget password later)
do{
 cout<<"Enter password:";
 cin>>user.password();
}while(user.password!=user_file.password);

}


void create_file(){
 cout<<"Enter username: ";
 cin>>user_name;
 ifstream User_info("users.txt");// to read the file of user and password
 while (User_info>>u.user_name >> u.password){ 
    //to avoid duplicate username;
      if(user_name==u.user_name){
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


};



int main(){
account a;
a.login_menu();
return 0;

 
}

