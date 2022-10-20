#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576
#define WIDTH 7
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);

    _tprintf(TEXT("There is  %*ld %% of memory in use.\n"),
             WIDTH, statex.dwMemoryLoad);
#endif

#ifdef linux
    char cmd[30];
    int flag = 0;
    FILE *fp;
    char line[130];
    int TotalMem, TotalFree, TotalUsed;

    flag = 0;
    memcpy(cmd, "\0", 30);
    sprintf(cmd, "free -t -m|grep Total");
    fp = popen(cmd, "r");
    while (fgets(line, sizeof line, fp))
    {
        flag++;
        sscanf(line, "%*s %d %d %d", &TotalMem, &TotalUsed, &TotalFree);
    }
    pclose(fp);

    if (flag)
        printf("TotalMem:%d -- TotalUsed:%d -- TotalFree:%d\n", TotalMem, TotalUsed, TotalFree);
    else
        printf("not found\n");
#endif

    return 0;
}