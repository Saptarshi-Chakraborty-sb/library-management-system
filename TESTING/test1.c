#include <stdio.h>
#include <windows.h>

void main()
{
    system("color 4");


    return;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("red text\n");

    SetConsoleTextAttribute(hConsole,0x7);

    printf("yellow on blue\n");
}