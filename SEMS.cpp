#include <iostream> 
#include <string>
#include <fstream> // file handling
#include <conio.h> // _getch()
#include <Windows.h> // Sleep()
using namespace std;

struct User {
    string username; 
    string password;
};

typedef struct student {
    string name;
    int id;
} user;

typedef struct Expense {
    int id; // Unique ID
    double amount; // Amount
    string date; // Format: DD-MM-YYYY
    string category; // Food, Travel, etc.
    string description; // Optional
} Expense;

// ------------------------ simple Caesar shift encrypt/decrypt ------------------------
int SHIFT = 3;

string encryptShift(string &s) {
    string out = s;
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        c = c + SHIFT;
        out[i] = c;
    }
    return out;
}

string decryptShift(string &s) {
    string out = s;
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        c = c - SHIFT;
        out[i] = c;
    }
    return out;
}

// ================================ ACCOUNT CLASS ===================================
class account {
public:
    bool login_success = false;
    static string username;
    friend class funtions;
    struct User user;
    struct User user_file;

    void login_menu() {
        int choice = 0;
        while (true) {
            system("cls");
            cout << (choice == 0 ? ">>" : " ") << "Login" << endl;
            cout << (choice == 1 ? ">>" : " ") << "Signup" << endl;

            char key = _getch();
            if (key == 72)
                choice = (choice + 1) % 2;
            else if (key == 80)
                choice = (choice + 1) % 2;
            else if (key == 13)
                break;
        }

        switch (choice + 1) {
        case 1:
            login();
            break;
        case 2:
            signup();
            break;
        }
    }

    void login() {
        bool user_exist = false;
        cout << "Enter username: ";
        cin >> user.username;

        ifstream User_info(".\\Account\\users.txt");
        string enc_u, enc_p;
        while (User_info >> enc_u >> enc_p) {
            string dec_u = decryptShift(enc_u);
            string dec_p = decryptShift(enc_p);
            if (user.username == dec_u) {
                user_exist = true;
                user_file.username = dec_u;
                user_file.password = dec_p;
                break;
            }
        }
        User_info.close();

        if (!user_exist) {
            cout << "User not found! Try again." << endl;
            Sleep(2000);
            login_menu();
            return;
        }

        do {
            cout << "Enter password: ";
            cin >> user.password;
        } while (user.password != user_file.password);

        cout << "Login successful!" << endl;
        Sleep(2000);
        system("cls");
        cout << "Welcome " << user.username << endl;
        username = user.username;
        login_success = true;
    }

    void signup() {
        cout << "Enter username: ";
        cin >> user.username;
        ifstream User_info(".\\Account\\users.txt");
        string enc_u2, enc_p2;
        while (User_info >> enc_u2 >> enc_p2) {
            string decu = decryptShift(enc_u2);
            if (user.username == decu) {
                cout << "User Already Exists!" << endl;
                Sleep(2000);
                User_info.close();
                login_menu();
                return;
            }
        }
        User_info.close();

        cout << "Enter password: ";
        cin >> user.password;

        ofstream file(".\\Data_base\\" + user.username + ".txt", ios::app);
        file.close();

        ofstream file1(".\\Account\\users.txt", ios::app);
        file1 << encryptShift(user.username) << " " << encryptShift(user.password) << endl;
        file1.close();

        cout << "Signup Successful!" << endl;
        Sleep(2000);
        login_menu();
    }
};

string account::username = "";

// ================================ FUNCTIONS CLASS ===================================
class funtions {
private:
    string username = account::username;
    int expenseCount = 0;
    Expense expense[500];

public:
    Expense input();
    string getDate();
    void addExpense();
    void viewExpense();
    void searchExpenseByMoney();
    void searchExpenseByDate();
    void sortExpense();
    void deleteExpense();
    void viewRecentExpenses();
    void loadExpenses();
    void saveExpenses();
    void totalExpenseByDate();
    void totalExpenseByMonth();
    void downloadExpenses();
    int dateToNumber(string &d);
};

// ----------------------- FUNCTION IMPLEMENTATIONS -----------------------------------

Expense funtions::input() {
    Expense expense;
    expense.id = expenseCount + 1;
    cout << "Enter the Category:(without space) ";
    cin >> expense.category;
    cin.ignore();
    cout << "Enter the description: ";
    getline(cin, expense.description);
    cout << "Enter the amount: ";
    cin >> expense.amount;
    cin.ignore();
    expense.date = getDate();
    expenseCount++;
    return expense;
}

string funtions::getDate() {
    int d, m, y;
    cout << "Enter day: ";
    cin >> d;
    cout << "Enter month: ";
    cin >> m;
    cout << "Enter year: ";
    cin >> y;
    return to_string(d) + "/" + to_string(m) + "/" + to_string(y);
}

void funtions::addExpense() {
    Expense e = input();
    expense[expenseCount - 1] = e;
    saveExpenses();
    cout << "Expense added successfully." << endl;
    Sleep(1000);
}

void funtions::viewExpense() {
    if (expenseCount == 0) {
        cout << "No Expenses Found" << endl;
        Sleep(1000);
    } else {
        cout << "----------- Expenses ------------" << endl;
        cout << "Id\tDate\t\tCategory\tAmount\tDescription" << endl;
        cout << "-----------------------------------------------" << endl;

        for (int i = 0; i < expenseCount; i++) {
            cout << expense[i].id << "\t" << expense[i].date << "\t" << expense[i].category << "\t" 
                 << expense[i].amount << "\t" << expense[i].description << endl;
        }
        cout << endl;
        cout << "Press any key to continue..." << endl;
        _getch();
    }
}

void funtions::searchExpenseByDate() {
    string dateToFind;
    cout << "Enter Date (Format dd/mm/yyyy): ";
    cin >> dateToFind;

    bool found = false;
    cout << "Search Results:" << endl;
    for (int i = 0; i < expenseCount; i++) {
        if (expense[i].date == dateToFind) {
            if (!found) {
                cout << "Id\tDate\t\tCategory\tAmount\tDescription" << endl;
                cout << "-----------------------------------------------" << endl;
            }
            cout << expense[i].id << "\t" << expense[i].date << "\t" << expense[i].category << "\t" 
                 << expense[i].amount << "\t" << expense[i].description << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No expenses found on that date." << endl;
    }
    cout << "Press any key to continue..." << endl;
    _getch();
}

void funtions::searchExpenseByMoney() {
    double low, high;
    cout << "Enter minimum amount: ";
    cin >> low;
    cout << "Enter maximum amount: ";
    cin >> high;
    bool found = false;
    cout << "Search Results:" << endl;
    for (int i = 0; i < expenseCount; i++) {
        if (expense[i].amount >= low && expense[i].amount <= high) {
            if (!found) {
                cout << "Id\tDate\t\tCategory\tAmount\tDescription" << endl;
                cout << "-----------------------------------------------" << endl;
            }
            cout << expense[i].id << "\t" << expense[i].date << "\t" << expense[i].category << "\t" 
                 << expense[i].amount << "\t" << expense[i].description << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No expenses found in that range." << endl;
    }
    cout << "Press any key to continue..." << endl;
    _getch();
}

int funtions::dateToNumber(string &d) {
    int day = 0, month = 0, year = 0;
    int part = 0;
    int val = 0;
    
    for (int i = 0; i < d.size(); i++) {
        if (d[i] == '/') {
            if (part == 0) day = val;
            else if (part == 1) month = val;
            val = 0;
            part++;
        } else {
            val = val * 10 + (d[i] - '0');
        }
    }
    year = val;
    return year * 10000 + month * 100 + day;
}

void funtions::sortExpense() {
    if (expenseCount == 0) {
        cout << "No expenses to sort." << endl;
        Sleep(1000);
        return;
    }
    cout << "Sort by: 1 = Amount, 2 = Date" << endl;
    cout << "Enter choice: ";
    int ch;
    cin >> ch;

    if (ch == 1) {
        for (int i = 0; i < expenseCount - 1; i++) {
            for (int j = 0; j < expenseCount - i - 1; j++) {
                if (expense[j].amount > expense[j + 1].amount) {
                    Expense temp = expense[j];
                    expense[j] = expense[j + 1];
                    expense[j + 1] = temp;
                }
            }
        }
        cout << "Sorted by amount (ascending)." << endl;
    } else if (ch == 2) {
        for (int i = 0; i < expenseCount - 1; i++) {
            for (int j = 0; j < expenseCount - i - 1; j++) {
                int da = dateToNumber(expense[j].date);
                int db = dateToNumber(expense[j + 1].date);
                if (da > db) {
                    Expense temp = expense[j];
                    expense[j] = expense[j + 1];
                    expense[j + 1] = temp;
                }
            }
        }
        cout << "Sorted by date (oldest first)." << endl;
    } else {
        cout << "Invalid option." << endl;
    }

    saveExpenses();
    Sleep(1000);
}

void funtions::deleteExpense() {
    if (expenseCount <= 0) {
        cout << "No expense to delete." << endl;
        Sleep(1000);
        return;
    }
    expenseCount--;
    cout << "Last expense deleted." << endl;
    saveExpenses();
    Sleep(1000);
}

void funtions::viewRecentExpenses() {
    int n = 5;
    cout << "Recent " << n << " expenses (latest first):" << endl;
    int printed = 0;
    for (int i = expenseCount - 1; i >= 0 && printed < n; i--) {
        cout << expense[i].id << "\t" << expense[i].date << "\t" << expense[i].category << "\t" 
             << expense[i].amount << "\t" << expense[i].description << endl;
        printed++;
    }
    if (printed == 0) cout << "No expenses yet." << endl;
    cout << "Press any key to continue..." << endl;
    _getch();
}
void funtions::totalExpenseByDate() {
    string d;
    cout<<"Enter date (dd/mm/yyyy): ";
    cin>>d;

    double sum = 0;

    for(int i=0; i<expenseCount; i++){
        if(expense[i].date == d){
            sum = sum + expense[i].amount;
        }
    }

    cout<<"Total on "<<d<<" = "<<sum<<endl;
    _getch();
}
void funtions::totalExpenseByMonth() {
    int month;
    cout << "Enter month (1-12): ";
    cin >> month;

    double sum = 0;

    for (int i = 0; i < expenseCount; i++) {
        int full = dateToNumber(expense[i].date);
        int m = (full / 100) % 100;    // extract month
        int y = full / 10000;          // extract year

        if (y == 2025 && m == month) // current year fixed
            sum += expense[i].amount;
    }

    cout << "Total for month " << month << " is: " << sum << endl;
    _getch();
}




void funtions::loadExpenses() {
    username = account::username;
    expenseCount = 0;

    string fname = ".\\Data_base\\" +username + ".txt";
    ifstream file(fname);
    if (!file) return;

    string line;

    while (getline(file, line)) {
        if (line == "") continue;

        string p1 = "", p2 = "", p3 = "", p4 = "", p5 = "";
        int commaCount = 0;

        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == ',') {
                commaCount++;
            } else {
                if (commaCount == 0) p1 += c;
                else if (commaCount == 1) p2 += c;
                else if (commaCount == 2) p3 += c;
                else if (commaCount == 3) p4 += c;
                else if (commaCount == 4) p5 += c;
            }
        }

        int idValue = stoi(p1);
        double amt = stod(p2);

        expense[expenseCount].id = idValue;
        expense[expenseCount].amount = amt;
        expense[expenseCount].date = p3;
        expense[expenseCount].category = p4;
        expense[expenseCount].description = p5;

        expenseCount++;
    }

    file.close();
}

void funtions::saveExpenses() {
    string fname =".\\Data_base\\"+ account::username + ".txt";
    ofstream out(fname);
    if (!out) return;

    for (int i = 0; i < expenseCount; i++) {
        out << expense[i].id << "," 
            << expense[i].amount << "," 
            << expense[i].date << "," 
            << expense[i].category << "," 
            << expense[i].description << "\n";
    }

    out.close();
}

// ----------------------- DOWNLOAD FUNCTION -----------------------------------
void funtions::downloadExpenses() {
    string sourceFile = ".\\Data_base\\" + account::username + ".txt";
    string destFile = ".\\Download\\" + account::username + "_backup.txt";

    ifstream in(sourceFile, ios::binary);
    if (!in) {
        cout << "Source file not found!" << endl;
        Sleep(1000);
        return;
    }

    ofstream out(destFile, ios::binary);
    if (!out) {
        cout << "Could not create download file!" << endl;
        Sleep(1000);
        return;
    }

    char ch;
    while (in.get(ch)) { // read character by character
        out.put(ch);     // write to new file
    }

    in.close();
    out.close();

    cout << "Expenses downloaded successfully to 'Download\\" << account::username << "_backup.txt'" << endl;
    Sleep(1500);
}

// ================================ MAIN FUNCTION ===================================
int main() {
    funtions f;
    account a;
    a.login_menu();

    if (a.login_success) {
        account::username = a.user.username;
        f.loadExpenses();

        while (true) {
            int choice = 0;
            while (true) {
                system("cls");
                cout << (choice == 0 ? ">>" : " ") << "Add Expense" << endl;
                cout << (choice == 1 ? ">>" : " ") << "View Expenses" << endl;
                cout << (choice == 2 ? ">>" : " ") << "Search Expense (By Money)" << endl;
                cout << (choice == 3 ? ">>" : " ") << "Search Expense (By Date)" << endl;
                cout << (choice == 4 ? ">>" : " ") << "Sort Expenses" << endl;
                cout << (choice == 5 ? ">>" : " ") << "Delete Expense" << endl;
                cout << (choice == 6 ? ">>" : " ") << "Recent Expenses" << endl;
                cout << (choice == 7 ? ">>" : " ") << "Download Expenses" << endl; 
                cout << (choice == 8 ? ">>" : " ") << "Total Expense By Date" << endl;
                cout << (choice == 9 ? ">>" : " ") << "Total Expense By Month" << endl;
                cout << (choice == 10 ? ">>" : " ") << "Save & Exit" << endl;

                char key = _getch();
                if (key == 72) choice = (choice + 10) % 11;
                else if (key == 80) choice = (choice + 1) % 11;
                else if (key == 13) break;
            }

            switch (choice) {
            case 0: f.addExpense(); break;
            case 1: f.viewExpense(); break;
            case 2: f.searchExpenseByMoney(); break;
            case 3: f.searchExpenseByDate(); break;
            case 4: f.sortExpense(); break;
            case 5: f.deleteExpense(); break;
            case 6: f.viewRecentExpenses(); break;
            case 7: f.downloadExpenses(); break; // new case
            case 8: f.totalExpenseByDate(); break;
            case 9: f.totalExpenseByMonth(); break;
            case 10:
                cout << "Saving and Exiting...\n";
                f.saveExpenses();
                Sleep(800);
                return 0;
            }
        }
    }
    return 0;
}
