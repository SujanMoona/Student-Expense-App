#include<iostream>
#include<string>
#include<vector>
#include<fstream>// File Handling 
#include<stack>
#include<ctime> // Library for Date & Time 
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


class functions{
private:
      int  expenseCount=0;// sr.no
      Expense expense[5];
      stack<Expense> undo,redo;//for undo redo 
      
public:
    void Register();
    void login();
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

void functions::addExpense(){
    expense[expenseCount]=input();// input
}

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
int main() {
  

    functions f;
    int choice;
    do{
        cout << "\n===== Expense Manager =====\n";
        cout << "1. Add Expense\n2. View Expenses\n3. Search Expense (By Money)\n";
        cout << "4. Search Expense (By Date)\n5. Sort Expenses\n6. Delete Expense\n";
        cout << "7. Undo Last Action\n8. Recent Expenses\n0. Save & Exit\n";
        cin >> choice;

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
        case 0:
            cout<<"Exiting...\n";
            break;            
        default:
            cout<<"Invalid Input! Enter Again\n";
            break;
        }
    } while (choice != 0);
}
