#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define __DATA_FOLDER ".LMS_DATA"
#define __DATA_STUDENTS_FILE ".LMS_DATA\\STUDENTS.txt"
#define __DATA_BOOKS_FILE ".LMS_DATA\\BOOKS.txt"
#define __DATA_ISSUE_FILE ".LMS_DATA\\ISSUE.txt"

int getLastStudentId();

void main()
{
    FILE *studentFile;
    char name[30], class[3], roll[4], section[2], year[5];
    char *tempStr1, *tempStr2;
    int lastIdNumber;

    system("cls");
    printf("\t--- Register New Student ---\n\n");
    printf("Enter student name (Max 30 character)\n$ ");
    gets(name);
    printf("Enter class (Max 2 character)\n$ ");
    scanf("%s", class);
    printf("Enter section (Max 2 character)\n$ ");
    scanf("%s", section);
    section[0] = toupper(section[0]);
    printf("Enter Roll Number (Max 3 character)\n$ ");
    scanf("%s", roll);

    // Automatically gets Year
    tempStr1 = (char *)malloc(sizeof(char) * 20);
    strcpy(tempStr1, __DATE__);
    strrev(tempStr1);
    strncpy(year, &tempStr1[0], 4);
    year[4] = '\0';
    strrev(year);
    free(tempStr1);

    lastIdNumber = getLastStudentId();

    studentFile = fopen(__DATA_STUDENTS_FILE, "a");
    if (studentFile == NULL)
    {
        printf("An Error Occurred during accessing Student file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(studentFile, "S%d,%s,%s,%s,%s,%s\n", (lastIdNumber + 1), name, class, section, roll, year);
    fclose(studentFile);

    printf("\n>> New Student Registered Successfully <<\n");
    printf("Name   : [%s]\nClass  : [%s]\nSection: [%s]\nRoll   : [%s]\nYear   : [%s]\n\n", name, class, section, roll, year);
    printf("New Student ID : S%d\n", lastIdNumber + 1);
}

/// @brief
/// @return 0 - if the file is empty
int getLastStudentId()
{
    FILE *studentFile;
    char sID[10], line[60];
    int count, isLine, idNumber, i = 0;

    studentFile = fopen(__DATA_STUDENTS_FILE, "r");

    // Check if the file is empty
    count = 0;
    while (fgetc(studentFile) != EOF)
        count++;
    if (count <= 2)
        return 0;
    fseek(studentFile, 0, SEEK_SET);

    while (fgets(line, sizeof(line), studentFile))
    {
    }
    fclose(studentFile);

    while (line[i++] != ',')
    {
    }

    strncpy(sID, &line[1], (i - 2));
    sID[i - 2] = '\0';

    return atoi(sID) ;
}