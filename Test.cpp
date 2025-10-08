#include <iostream>
#include <conio.h>  // for getch()
using namespace std;

int main() {
    int choice = 0;
    char key;

    while (true) {
        system("cls");  // clear screen (Windows)
        cout << "Use UP/DOWN arrows, Enter to select:\n\n";

        cout << (choice == 0 ? ">> " : "   ") << "Create File\n";
        cout << (choice == 1 ? ">> " : "   ") << "Search File\n";
        cout << (choice == 2 ? ">> " : "   ") << "Exit\n";

        key = _getch();
        if (key == 72) choice = (choice + 2) % 3;  // UP arrow
        else if (key == 80) choice = (choice + 1) % 3;  // DOWN arrow
        else if (key == 13) break;  // Enter key
    }

    cout << "\nYou selected option " << choice + 1 << endl;
    return 0;
}