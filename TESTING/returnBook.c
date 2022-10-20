#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define __DATA_FOLDER ".LMS_DATA"
#define __DATA_STUDENTS_FILE ".LMS_DATA\\STUDENTS.txt"
#define __DATA_BOOKS_FILE ".LMS_DATA\\BOOKS.txt"
#define __DATA_ISSUE_FILE ".LMS_DATA\\ISSUE.txt"

int strpos(char *, char);
int isValidStudentId(char *);
int isBookAvailable(char *);
int changeBookCopy(char *, int, int);

void main()
{
    FILE *issueFile, *bookFile, *tempFile;
    char sID[10] = "S1", bID[10] = "B02", line[250], bookId[11], studentId[11], tempLine[260], ch;
    char *tempFileName = ".bookIssue.temp.txt", newCopyNumber[4];
    int isValidStudent, bookAvailavility, commaPos, prevPos, bookCopyChange;

    printf("-- Book Return --\n");

    printf("Enter student id : ");
    scanf("%s", sID);
    sID[0] = 'S';

    isValidStudent = isValidStudentId(sID);
    if (isValidStudent != 0)
    {
        printf("Invalid Student ID\n");
        return;
    }

    printf("Enter book id : ");
    scanf("%s", bID);
    bID[0] = 'B';
    bID[1] = '0';

    bookAvailavility = isBookAvailable(bID);
    if (bookAvailavility == -1)
    {
        printf("En error occured\n");
        exit(EXIT_FAILURE);
    }

    // Increment Number of Copies of that Book
    bookCopyChange = changeBookCopy(bID, bookAvailavility, 1);
    if (bookCopyChange != 1)
        printf(" !!! Book Copy Increment function error. Returned = %d !!!\n", bookCopyChange);

    // remove the entry from ISSUE file

    issueFile = fopen(__DATA_ISSUE_FILE, "r");
    tempFile = fopen(tempFileName, "w");

    while (fgets(line, sizeof line, issueFile))
    {
        // printf("line = [%s]\n", line);
        prevPos = 0;
        commaPos = strpos(&line[prevPos], ',');
        prevPos += (commaPos + 1);

        strncpy(studentId, line, commaPos);
        studentId[commaPos] = '\0';

        if (strcmp(studentId, sID) == 0)
        {
            commaPos = strpos(&line[prevPos], ',');
            strncpy(bookId, &line[prevPos], commaPos);
            bookId[commaPos] = '\0';

            if (strcmp(bookId, bID) == 0)
                continue;
        }
        fputs(line, tempFile);
    }
    fclose(issueFile);
    fclose(tempFile);

    issueFile = fopen(__DATA_ISSUE_FILE, "w");
    tempFile = fopen(tempFileName, "r");

    while (ch != EOF)
    {
        ch = getc(tempFile);
        if (ch != EOF)
            putc(ch, issueFile);
    }

    fclose(issueFile);
    fclose(tempFile);
    unlink(tempFileName);

    printf("\t>> BOOK RETURNED SUCCESSFULLY <<\n");
}

/// @brief
/// @param sID
/// @return 0 = if student id is valid ; 1 = if student id is invalid ; (-1) = if any error occured
int isValidStudentId(char *sID)
{
    FILE *studentFile;
    char line[50], gotID[10];
    int commaPos, flag = 0;

    studentFile = fopen(__DATA_STUDENTS_FILE, "r");
    if (studentFile == NULL)
        return -1;
    if (fgetc(studentFile) == EOF)
    {
        printf("\t--- No Student Data Found ---\n");
        return -1;
    }
    fseek(studentFile, 0, SEEK_SET);

    while (fgets(line, sizeof line, studentFile))
    {
        commaPos = strpos(line, ',');
        strncpy(gotID, line, commaPos);
        gotID[commaPos] = '\0';
        if (stricmp(gotID, sID) == 0)
        {
            flag = 1;
            break;
        }
    }
    fclose(studentFile);

    if (flag == 1)
        return 0;
    else
        return 1;
}

int isBookAvailable(char *_bookID)
{
    FILE *bookFile;
    char newBookId[10], noOfCopiesInChar[3], line[250];
    int commaPos, prevPos, flag = 0;

    bookFile = fopen(__DATA_BOOKS_FILE, "r");
    if (bookFile == NULL)
    {
        printf("Error during opening Books File\n");
        return -1;
    }
    if (fgetc(bookFile) == EOF)
    {
        printf("\t--- No Books Data Found ---\n");
        return -1;
    }

    fseek(bookFile, 0, SEEK_SET);

    while (fgets(line, sizeof line, bookFile))
    {
        prevPos = 0;
        commaPos = strpos(&line[prevPos], ',');
        prevPos += (commaPos + 1);
        strncpy(newBookId, &line[0], commaPos);
        newBookId[commaPos] = '\0';
        // printf("id = [%s]\n", newBookId);
        if (stricmp(newBookId, _bookID) != 0)
            continue;

        commaPos = strpos(&line[prevPos], ',');
        prevPos += (commaPos + 1);
        commaPos = strpos(&line[prevPos], ',');
        prevPos += (commaPos + 1);
        commaPos = strpos(&line[prevPos], ',');
        prevPos += (commaPos + 1);
        commaPos = strpos(&line[prevPos], ',');

        strncpy(noOfCopiesInChar, &line[prevPos], commaPos);
        noOfCopiesInChar[commaPos] = '\0';
        fclose(bookFile);
        return atoi(noOfCopiesInChar);
    }

    fclose(bookFile);
    return -1;
}

int strpos(char *str, char ch)
{
    int count = 0, i = 0;
    while (str[i] != '\0')
    {
        if (str[i++] == ch)
            return (i - 1);
    }
    return -1;
}

int changeBookCopy(char *bID, int bookAvailavility, int _changeBy)
{
    FILE *issueFile, *bookFile, *tempFile;
    char line[250], bookId[10], tempLine[260], ch;
    char *tempFileName = ".bookIssue.temp.txt", newCopyNumber[4];
    int isValidStudent, commaPos, prevPos;
    bookFile = fopen(__DATA_BOOKS_FILE, "r");
    tempFile = fopen(tempFileName, "w");

    while (fgets(line, sizeof line, bookFile))
    {
        // printf("line = [%s]\n", line);
        prevPos = 0;

        commaPos = strpos(&line[prevPos], ',');
        strncpy(bookId, line, commaPos);
        bookId[commaPos] = '\0';

        if (stricmp(bookId, bID) == 0)
        {
            prevPos += (commaPos + 1);
            commaPos = strpos(&line[prevPos], ',');
            prevPos += (commaPos + 1);
            commaPos = strpos(&line[prevPos], ',');
            prevPos += (commaPos + 1);
            commaPos = strpos(&line[prevPos], ',');
            prevPos += (commaPos + 1);

            strncpy(tempLine, line, prevPos);
            tempLine[prevPos] = '\0';

            sprintf(newCopyNumber, "%d", (bookAvailavility + _changeBy));
            strcat(tempLine, newCopyNumber);

            commaPos = strpos(&line[prevPos], ',');
            prevPos += commaPos;
            strcat(tempLine, &line[prevPos]);

            // printf("templine = [%s]\n", tempLine);
            fputs(tempLine, tempFile);

            continue;
        }

        fputs(line, tempFile);
        // printf("line = [%s]\n", line);
    }
    fclose(bookFile);
    fclose(tempFile);

    // copy temprary file content in book file
    bookFile = fopen(__DATA_BOOKS_FILE, "w");
    tempFile = fopen(tempFileName, "r");
    while (ch != EOF)
    {
        ch = fgetc(tempFile);
        if (ch != EOF)
            fputc(ch, bookFile);
    }
    fclose(bookFile);
    fclose(tempFile);
    unlink(tempFileName); // delete temporary file
    return 1;
}