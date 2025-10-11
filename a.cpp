#ifdef _WIN32
#include <windows.h>
void gotoxy(int x,int y){
  COORD pos; pos.X = x; pos.Y = y; // 0-based
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
#endif 
#include<iostream>
int main()
{
    gotoxy(10,5); std::cout << "Hello at (10,5)";

}
