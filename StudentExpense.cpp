#include<iostream>
#include<string>
#include<vector>
#include<fstream>// File Handling 
#include<stack>
#include<ctime>// Library for Date & Time 
#include<conio.h>
#include<Windows.h> 
using namespace std;

struct User
{
    string username; 
    string password;
    
};

typedef struct student{
string name;
int id;
}user;

typedef struct Expense {
    int id;                // Unique ID
    double amount;         // Amount
    string date;           // Format: DD-MM-YYYY
    string category;       // Food, Travel, etc.
    string description;    // Optional
    
}Expense;




// login class handling the login and files 
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


class account{
 
public:
bool login_success=false;// used in the main funtion 
static string username;
friend class funtions;
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
          
                login();
                break;
            }
            
        
        case 2:{
                signup();
                break;
        }
    }


   /* if(signup || l){
    cout<<(l? "login succesful":"signup succesful")<<endl;
        
    }*/

 

}

void login(){
    bool user_exist=false;
    cout<<"Enter username:";
    cin>>user.username;

    ifstream User_info("users.txt");// to read the file of user and password
    while (User_info>>user_file.username >> user_file.password){ 
    //to avoid duplicate username;
      if(user.username==user_file.username){
        user_exist=true;
      break;// it means user is  exist;
      }
     }
    if(!user_exist){
    cout<<"user not found! try again"<<endl;
  
    Sleep(2000);//to dealy the call login menu call bu 2000 milisecond i.e 2 sec;
    login_menu();
    }
 //run until password is correct ..(we can also thinking about adding forget password later)
 //change the fromating----task rmeainig
 
do{
 cout<<"Enter password:";
 cin>>user.password;
}while(user.password!=user_file.password);
cout<<"Login succesfull"<<endl;
Sleep(2000);
system("cls");
cout<<"Welcome "<<user.username<<endl;
username=user.username;// this static used to access the username in the funtions class
login_success=true; 
}


void signup(){
 cout<<"Enter username: ";
 cin>>user.username;
 ifstream User_info("users.txt");// to read the file of user and password
 while (User_info>>user_file.username >> user_file.password){ 
    //to avoid duplicate username;
      if(user.username==user_file.username){
        cout<<"User Already Exist"<<endl;
        Sleep(2000);// to delay the login menu by 2 sec;
        login_menu();
    }
}
User_info.close();
    cout<<"Enter password: ";
    cin>>user.password;

 //user_name=user_name+".txt";
 ofstream file(user.username+".txt");
 file<<"This is the msg we have to print;";
 file.close();

 ofstream file1("users.txt",ios::app );
 file1<<user.username<<" "<<user.password<<endl;
 file1.close();
 
 cout<<"signup Successful!"<<endl;
 Sleep(2000);
 login_menu();//now after sign up go to login;
}



};

string account::username = "";
//end of the login class=======================================================================================================
//=============================================================================================================================
//=============================================================================================================================
class functions{
private:
      
      string username= account::username;
      int  expenseCount=0;// sr.no
      Expense expense[5];
      stack<Expense> undo,redo;//for undo redo 
      
      
public:
    Expense input();
    string getDate();
    void addExpense();         // 1. Add Expense
    void viewExpense();       // 2. View Expenses
    void searchExpenseByMoney();  // 3. Search Expense (By Money)
    void searchExpenseByDate(); // 4. Search Expense (By Date)  
    void sortExpense();       // 5. Sort Expenses
    void deleteExpense();      // 6. Delete Expense
    void undoLastAction();     // 7. Undo Last Action
    void viewRecentExpenses(); // 8. Recent Expenses
    
};

//=============================================================================================================================
//=============================================================================================================================
//=============================================================================================================================
Expense functions::input(){
    Expense expense;
    expense.id = expenseCount+1;
    cout<<"Enter the Category";
    cin>>expense.category;
    cout<<"Enter the description:";
    getline(cin,expense.description);
    cout<<"Enter the amount :";
    cin>>expense.amount;
    expense.date = getDate();
    expenseCount++;
    undo.push(expense);//for keep the privious actions;
    return expense;

}
//=============================================================================================================================
//=============================================================================================================================

string functions::getDate(){
    // Get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int day = ltm->tm_mday;
    int month = 1 + ltm->tm_mon;
    int year = 1 + ltm->tm_year;

    // Convert To String 
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}
//==============================================================================================================================
//==============================================================================================================================

void functions::addExpense(){
    expense[expenseCount]=input();// input
}

//==============================================================================================================================
//==============================================================================================================================
void functions::viewExpense(){
    if (expenseCount == 0){
        cout<<"No Expenses Found"<<endl;
    }else {
        cout<<"----------- Expenses ------------"<<endl;
        cout<<"Id\tDate\tCategory\tAmount\tDescription"<<endl;
        cout<<"---------------------------------"<<endl;

        for ( int i = 0; i < expenseCount ; i++){
            cout<<expense[i].id<<"\t";
            cout<<expense[i].date<<"\t";
            cout<<expense[i].category<<"\t";
            cout<<expense[i].amount<<"\t";
            cout<<expense[i].description;
        }
        cout<<endl;
    }
}

void functions::searchExpenseByDate(){
    string dateToFind;
    cout<<"Enter Date (Format dd/mm/yyyy): ";
    cin>>dateToFind;

    
}

void functions::searchExpenseByMoney(){
    //Yet to be developed
}


void functions::sortExpense(){
    //Yet to be developed
}

void functions::viewRecentExpenses(){
    //Yet to be developed
}

void functions::undoLastAction(){
    if(undo.empty()){
     cout<<"Undo is not possible"<<endl;
    }else{
     redo.push(undo.top());
     undo.pop();
    }
}
void functions::deleteExpense(){
    expenseCount--;
}




//==============================================================================================================================
//==============================================================================================================================
//==============================================================================================================================
int main() {
  

    functions f;
    account a;
    a.login_menu();
    if(a.login_success){
    int choice=0;
     while (true) {
        system("cls");
        cout<<(choice==0?">>" :" ")<<"Add Expense"<<endl; 
        cout<<(choice==1?">>" :" ")<<"View Expenses"<<endl;
        cout<<(choice==2?">>" :" ")<<"Search Expense (By Money)"<<endl;
        cout<<(choice==3?">>" :" ")<<"Search Expense (By Date)"<<endl;
        cout<<(choice==4?">>" :" ")<<"Sort Expenses"<<endl;
        cout<<(choice==5?">>" :" ")<<"Delet Expense"<<endl;
        cout<<(choice==6?">>" :" ")<<"Undo Last Action"<<endl;
        cout<<(choice==7?">>" :" ")<<"Recent Expenses"<<endl;
        cout<<(choice==8?">>" :" ")<<"Save & Exit"<<endl;
     
    

        char key=_getch();
        if(key==72){
                choice=(choice+8)%9;
        }else if(key==80){
                choice=(choice+1)%9;
        }else if(key==13){
                break;
        }

    }

        switch (choice)
        {
        case 1:
            f.addExpense();
            break;
        case 2: 
            f.viewExpense();
            break;
        case 3:
            f.searchExpenseByMoney();
            break;
        case 4:
            f.searchExpenseByDate();
            break;
        case 5:
            f.sortExpense();
            break;
        case 6:
            f.deleteExpense();
            break;
        case 7:
            f.undoLastAction();
            break;
        case 8:
            f.viewRecentExpenses();
            break;
        case 9:
            cout<<"Exiting...\n";
            break;            
        default:
            cout<<"Invalid Input! Enter Again\n";
            break;
        }
        return 0;
    }
}

    
//==============================================================================================================================
//==============================================================================================================================