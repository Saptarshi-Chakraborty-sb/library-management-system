#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define __DATA_FOLDER ".LMS_DATA"
#define __DATA_STUDENTS_FILE ".LMS_DATA\\STUDENTS.txt"
#define __DATA_BOOKS_FILE ".LMS_DATA\\BOOKS.txt"
#define __DATA_ISSUE_FILE ".LMS_DATA\\ISSUE.txt"

int getLastBookId();

void main()
{
    FILE *bookFile;
    char name[70], author[70], publisher[50], noOfcopies[3];
    int lastBookId;

    system("cls");
    // Take input All Data about the book
    printf("\t--- Add New Book ---\n\n");
    printf("Enter Book Name (Max 70 character)\n$ ");
    gets(name);
    printf("Enter Author Name (Max 70 character)\n$ ");
    gets(author);
    printf("Enter publisher (Max 50 character, optional)\n$ ");
    gets(publisher);
    printf("Enter number of copies\n$ ");
    scanf("%s", noOfcopies);
    lastBookId = getLastBookId();

    // Now open books file
    bookFile = fopen(__DATA_BOOKS_FILE, "a");
    if (bookFile == NULL)
    {
        printf("An Error Occurred during openning Book file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(bookFile, "B0%d,%s,%s,%s,%s,%s,%s\n", (lastBookId + 1), name, author, publisher, noOfcopies, __DATE__, __TIME__);
    fclose(bookFile);

    printf("\n>> New Book Added Successfully <<\n");
    printf("Name         : [%s]\nAuthor       : [%s]\nPublisher    : [%s]\nNo of Copies : [%s]\nAdded at     : [%s][%s]\n", name, author, publisher, noOfcopies, __DATE__, __TIME__);
    printf(">> New Book Unique ID : B0%d <<\n", lastBookId + 1);

    fclose(bookFile);
}

int getLastBookId()
{
    FILE *bookFile;
    char bID[10], line[250];
    int count, i = 0;

    bookFile = fopen(__DATA_BOOKS_FILE, "r");

    // Check if the file is empty
    count = 0;
    while (fgetc(bookFile) != EOF)
        count++;
    if (count <= 2)
        return 0;
    fseek(bookFile, 0, SEEK_SET);

    while (fgets(line, sizeof(line), bookFile));
    fclose(bookFile);

    while (line[i++] != ',');

    strncpy(bID, &line[2], (i - 2));
    bID[i - 2] = '\0';

    return atoi(bID);
}