#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <synchapi.h>
#include <minwindef.h>

void takeInput(char *, int);

void main()
{
    char MyInput[100], *pointerInput;
    int maxSize = 10;
        system("cls");
    printf("Hello 1st Sentence\n");

    while (1)
    {
        printf("\b_");
        Sleep(1000);
        printf("\b ");
        Sleep(1000);
    }

    printf("After loop\n");

    return;
    pointerInput = (char *)malloc(sizeof(char) * 10);
    takeInput(pointerInput, 10);
    printf("Returned [%s]", pointerInput);
}

void takeInput(char *_Str, int _maxSize)
{
    int length, i = 0;
    char ch;
    while (ch != '\n' && i <= _maxSize)
    {
        ch = getchar();
        _Str[i++] = ch;
    }
    _Str[i - 1] = '\0';
    // printf("String : [%s]\n", _Str);
}