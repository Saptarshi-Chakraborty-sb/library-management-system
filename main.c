
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

#define __DATA_FOLDER ".LMS_DATA"
#define __DATA_STUDENTS_FILE ".LMS_DATA\\STUDENTS.txt"
#define __DATA_BOOKS_FILE ".LMS_DATA\\BOOKS.txt"
#define __DATA_ISSUE_FILE ".LMS_DATA\\ISSUE.txt"

#if defined(_WIN32) || defined(_WIN64)
#define _CLEAR_TERMINAL_ system("cls");
#elif defined(__linux__) || defined(__APPLE__)
#define _CLEAR_TERMINAL_ system("clear");
#endif

// Primary Functions
int controlFunction();
int checkStatus();
int registerNewStudent();
int registerNewBook();
int showStudentsDetails();
int showBooksDetails();
int issueBook();
int returnBook();

// Secondary Function
int isFile(char *);
void takeInput(char *, int);
int getLastStudentId();
int getLastBookId();
int strpos(char *, char);
int isValidStudentId(char *);
int noOfBooksAvailable(char *);
int changeBookCopy(char *, int, int);

void main()
{
    controlFunction();
}

/// 📢 Primary Functions :-

int controlFunction()
{
    int input, returnValue;

    while (1)
    {
        input = checkStatus();
        if (input == 1)
        {
            printf("There are some error during initializing the System.\n");
            return 1;
        }

        printf(" [1] - Register New Student\n");
        printf(" [2] - Add New Book\n");
        printf(" [3] - Issue a Book\n");
        printf(" [4] - Return a Book\n");
        printf(" [5] - Show all Students\n");
        printf(" [6] - Show all Books\n");
        printf(" [Other] - Exit\n $ ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            returnValue = registerNewStudent();
            break;

        case 2:
            printf("Add New Book\n");
            returnValue = registerNewBook();
            break;

        case 3:
            printf("Issue a Book\n");
            returnValue = issueBook();
            break;

        case 4:
            printf("Return a Book\n");
            returnValue = returnBook();
            break;

        case 5:
            printf("Show all students\n");
            returnValue = showStudentsDetails();
            break;

        case 6:
            printf("Show all books\n");
            returnValue = showBooksDetails();
            break;

        default:
            printf(" --- THANK YOU FOR USING  \"LIBRARY MANAGEMENT SYSTEM\" ---");
            printf("\n\t__created by, Saptarshi Chakraborty");
            return 0;
            break;
        }
    }
}

int checkStatus()
{
    FILE *fp;
    char *tempStr1;

    if ((isFile(__DATA_STUDENTS_FILE) == 1) || (isFile(__DATA_BOOKS_FILE) == 1) || (isFile(__DATA_ISSUE_FILE) == 1))
    {
        printf("The Library Management System is not used before.\nYou have to initialize it when using for the First Time.\n\n>> Enter 'yes' to initialize the system (this is a one time process)\n>> Enter any other key to cancel\n$ ");

        tempStr1 = (char *)malloc(sizeof(char) * 3);
        gets(tempStr1);
        if (strcmpi("yes", tempStr1) != 0)
            return 1;
        free(tempStr1);
        mkdir(__DATA_FOLDER);
        fp = fopen(__DATA_BOOKS_FILE, "w");
        if (fp == NULL)
            return 1;
        fclose(fp);
        fp = fopen(__DATA_STUDENTS_FILE, "w");
        if (fp == NULL)
            return 1;
        fclose(fp);
        fp = fopen(__DATA_ISSUE_FILE, "w");
        if (fp == NULL)
            return 1;
        fclose(fp);

        
        #if defined(_WIN32) || defined(_WIN64)
            SetFileAttributes(".LMS_DATA\\", FILE_ATTRIBUTE_HIDDEN); // hides lms_data folder (needs windows.h header file)
        #endif
            return 0;
    }
    // printf("ALL FILES OKAY\n");
    return 0;
}

int registerNewStudent()
{
    FILE *studentFile;
    char class[3], roll[4], section[2], year[5];
    char name[30], fname[14], lname[14];
    char *tempStr1, *tempStr2;
    int lastIdNumber, length;

    _CLEAR_TERMINAL_
    printf("\t--- Register New Student ---\n\n");

    printf("Enter Student name\n$ ");
    scanf("%s %s", fname, lname);

    length = strlen(fname);
    if (length > 14)
        fname[14] = '\0';
    length = strlen(lname);
    if (length > 14)
        lname[14] = '\0';

    sprintf(name, "%s %s", fname, lname);

    printf("Enter class\n$ ");
    scanf("%s", class);

    printf("Enter Section\n$ ");
    scanf("%s", section);
    section[0] = toupper(section[0]);

    printf("Enter roll\n$ ");
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
    printf("Name   : [%s]\nClass  : [%s]\nSection: [%s]\nRoll   : [%s]\nYear   : [%s]\n", name, class, section, roll, year);
    printf(">> New Student ID : S%d\n\n", lastIdNumber + 1);

    return 0;
}

int registerNewBook()
{
    FILE *bookFile;
    // char name[70], author[70], publisher[50], noOfcopies[3], ch;
    char publisher[50], noOfcopies[3], ch;
    char *name, *author;
    int lastBookId, i = 0;

    name = (char *)malloc(sizeof(char) * 70);
    author = (char *)malloc(sizeof(char) * 70);

    // Take input All Data about the book
    printf("\t--- Add New Book ---\n\n");
    printf("Enter Book Name (Max 70 character)\n$ ");
    gets(name);
    takeInput(name, 70);

    printf("Enter Author Name (Max 70 character)\n$ ");
    takeInput(author, 70);
    printf("Enter publisher (Max 50 character, optional)\n$ ");
    takeInput(publisher, 50);
    printf("Enter number of copies\n$ ");
    takeInput(noOfcopies, 2);

    lastBookId = getLastBookId();

    // printf("Name: [%s]\nAuthor: [%s]\nPublisher: [%s]\nNumber of Copies: [%s]\nLast Book Id: [%d]\n\n", name, author, publisher, noOfcopies, lastBookId);

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

int showStudentsDetails()
{
    FILE *studentFile;
    char line[60], ch = 'c', sID[10], name[30], class[2], section[1], roll[3], year[4];
    int count, length, commaPos, prevPos;

    studentFile = fopen(__DATA_STUDENTS_FILE, "r");

    _CLEAR_TERMINAL_

    // Checks if the file is Empty
    if (fgetc(studentFile) == EOF)
    {
        printf("\t--- No Student Data Found ---\n");
        return 1;
    }
    fseek(studentFile, 0, SEEK_SET);

    printf("\t\t  --- ALL STUDENTS DETAILS ---\n\n");
    printf("  %-3s |              %-17s | %-2s | %-s | %-3s | %-4s\n", "ID", "NAME", "CLASS", "SEC", "ROLL", "YEAR");
    printf(" ------------------------------------------------------------------\n");

    while (fgets(line, sizeof line, studentFile))
    {
        prevPos = 0;

        // Itrate sID
        commaPos = strpos(line, ',');
        strncpy(sID, line, commaPos);
        sID[commaPos] = '\0';
        printf("  %-3s |", sID);
        prevPos += (commaPos + 1);

        // Itrate Name
        commaPos = strpos(&line[prevPos], ',');
        strncpy(name, &line[prevPos], commaPos);
        name[commaPos] = '\0';
        printf(" %-30s |", name);
        prevPos += (commaPos + 1);

        // Itrate Class
        commaPos = strpos(&line[prevPos], ',');
        strncpy(class, &line[prevPos], commaPos);
        class[commaPos] = '\0';
        printf(" %-5s |", class);
        prevPos += (commaPos + 1);

        // Itrate Section
        commaPos = strpos(&line[prevPos], ',');
        strncpy(section, &line[prevPos], commaPos);
        section[commaPos] = '\0';
        printf(" %-3s |", section);
        prevPos += (commaPos + 1);

        // Itrate Roll
        commaPos = strpos(&line[prevPos], ',');
        strncpy(roll, &line[prevPos], commaPos);
        roll[commaPos] = '\0';
        printf(" %-4s |", roll);
        prevPos += (commaPos + 1);

        // Itrate Year
        commaPos = strpos(&line[prevPos], '\n');
        strncpy(year, &line[prevPos], commaPos);
        year[commaPos] = '\0';
        printf(" %-4s \n", year);
        prevPos += (commaPos + 1);
    }

    printf("\n\n");
    fclose(studentFile);
    return 0;
}

int showBooksDetails()
{
    FILE *bookFile;
    char line[200], ch = 'c', bID[10], name[70], author[70], publication[50], noOfCopies[3], date[12], time[8];
    int count, length, commaPos, prevPos;

    bookFile = fopen(__DATA_BOOKS_FILE, "r");

    _CLEAR_TERMINAL_

    // Checks if the file is Empty
    if (fgetc(bookFile) == EOF)
    {
        printf("\t--- No Books Data Found ---\n");
        return 1;
    }
    fseek(bookFile, 0, SEEK_SET);

    printf("\t\t  --- ALL BOOKS DETAILS ---\n\n");
    printf("  %-3s | %-20s | %-20s | %-20s | %-3s | %-4s\n", "ID", "NAME", "AUTHOR", "PUBLICATION", "NO OF COPIES", "ADDED AT");
    printf(" ---------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof line, bookFile))
    {
        // printf("Line = [%s]\n",line);
        prevPos = 0;

        // Itrate bID
        commaPos = strpos(line, ',');
        strncpy(bID, line, commaPos);
        bID[commaPos] = '\0';
        printf("  %-3s |", bID);
        prevPos += (commaPos + 1);

        // Itrate Name
        commaPos = strpos(&line[prevPos], ',');
        strncpy(name, &line[prevPos], commaPos);
        name[commaPos] = '\0';
        printf(" %s |", name);
        prevPos += (commaPos + 1);

        // Itrate Author
        commaPos = strpos(&line[prevPos], ',');
        strncpy(author, &line[prevPos], commaPos);
        author[commaPos] = '\0';
        printf(" %s |", author);
        prevPos += (commaPos + 1);

        // Itrate Publication
        commaPos = strpos(&line[prevPos], ',');
        strncpy(publication, &line[prevPos], commaPos);
        publication[commaPos] = '\0';
        printf(" %s |", publication);
        prevPos += (commaPos + 1);

        // Itrate Number of Copies
        commaPos = strpos(&line[prevPos], ',');
        strncpy(noOfCopies, &line[prevPos], commaPos);
        noOfCopies[commaPos] = '\0';
        printf(" %-4s |", noOfCopies);
        prevPos += (commaPos + 1);

        // Itrate Date
        commaPos = strpos(&line[prevPos], ',');
        strncpy(date, &line[prevPos], commaPos);
        date[commaPos] = '\0';
        printf(" %-12s ", date);
        prevPos += (commaPos + 1);

        // Itrate Time
        commaPos = strpos(&line[prevPos], '\n');
        strncpy(time, &line[prevPos], commaPos);
        time[commaPos] = '\0';
        printf("%-8s \n", time);
        prevPos += (commaPos + 1);
    }

    printf("\n\n");

    fclose(bookFile);
    return 0;
}

int issueBook()
{

    FILE *issueFile, *bookFile, *tempFile;
    char sID[10] = "S1", bID[10] = "B02", line[250], bookId[10], tempLine[260], ch;
    char *tempFileName = ".bookIssue.temp.txt", newCopyNumber[4];
    int isValidStudent, bookAvailability, commaPos, prevPos, bookCopyChange;

    _CLEAR_TERMINAL_

    printf("-- Book Issue --\n");

    printf("Enter student id : ");
    scanf("%s", sID);
    sID[0] = 'S';

    isValidStudent = isValidStudentId(sID);
    if (isValidStudent != 0)
    {
        printf("Invalid Student ID\n");
        return 1;
    }

    printf("Enter book id : ");
    scanf("%s", bID);
    bID[0] = 'B';
    bID[1] = '0';

    bookAvailability = noOfBooksAvailable(bID);
    if (bookAvailability == -1)
    {
        printf("En error occured\n");
        exit(EXIT_FAILURE);
    }
    else if (bookAvailability == 0)
    {
        printf("!!! This book is currently Out of Stock !!!\n");
        return 2;
    }

    // Increment Number of Copies of that Book
    bookCopyChange = changeBookCopy(bID, bookAvailability, -1);
    if (bookCopyChange != 0)
    {
        printf(" !!! Book Copy Decrement function error. Returned = %d !!!\n", bookCopyChange);
        return 2;
    }

    issueFile = fopen(__DATA_ISSUE_FILE, "a+");
    fprintf(issueFile, "%s,%s,%s,%s\n", sID, bID, __DATE__, __TIME__);
    fclose(issueFile);

    printf("\t>> BOOK ISSUED SUCCESSFULLY <<\n");
    return 0;
}

int returnBook()
{
    FILE *issueFile, *bookFile, *tempFile;
    char sID[10] = "S1", bID[10] = "B02", line[250], bookId[11], studentId[11], tempLine[260], ch;
    char *tempFileName = ".bookIssue.temp.txt", newCopyNumber[4];
    int isValidStudent, bookAvailability, commaPos, prevPos, bookCopyChange;

    _CLEAR_TERMINAL_

    printf("-- Book Return --\n");

    printf("Enter student id : ");
    scanf("%s", sID);
    sID[0] = 'S';

    isValidStudent = isValidStudentId(sID);
    if (isValidStudent != 0)
    {
        printf("Invalid Student ID\n");
        return 1;
    }

    printf("Enter book id : ");
    scanf("%s", bID);
    bID[0] = 'B';
    bID[1] = '0';

    bookAvailability = noOfBooksAvailable(bID);
    if (bookAvailability == -1)
    {
        printf("En error occured\n");
        exit(EXIT_FAILURE);
    }

    // Increment Number of Copies of that Book
    bookCopyChange = changeBookCopy(bID, bookAvailability, 1);
    if (bookCopyChange != 0)
    {
        printf(" !!! Book Copy Increment function error. Returned = %d !!!\n", bookCopyChange);
        return 2;
    }

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
    return 0;
}

/// 📢 Secondary Function :-

/// @brief Function to check if a file exists
/// @return 0 - if the file is exists, else 1
int isFile(char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp)
        return 0;
    return 1;
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

    return atoi(sID);
}

/// @brief Function to take string input of predefined size
/// @param _str Character pointer of the string
/// @param _maxSize Max size of the string
void takeInput(char *_str, int _maxSize)
{
    int length, i = 0;
    char ch;
    while (ch != '\n' && i <= _maxSize)
    {
        ch = getchar();
        _str[i++] = ch;
    }
    _str[i - 1] = '\0';
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

    while (fgets(line, sizeof(line), bookFile))
        ;
    fclose(bookFile);

    while ((line[++i] != ','))
        ;

    strncpy(bID, &line[2], (i - 2));
    bID[i - 2] = '\0';

    return atoi(bID);
}

/// @brief Gives position of the first occurrence of a character in a string. Case-sensitive
/// @param str
/// @param ch
/// @return integer
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

int noOfBooksAvailable(char *_bookID)
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
        return -2;
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

int changeBookCopy(char *bID, int bookAvailability, int _changeBy)
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

            sprintf(newCopyNumber, "%d", (bookAvailability + _changeBy));
            strcat(tempLine, newCopyNumber);

            commaPos = strpos(&line[prevPos], ',');
            prevPos += commaPos;
            strcat(tempLine, &line[prevPos]);

            fputs(tempLine, tempFile);

            continue;
        }

        fputs(line, tempFile);
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
    return 0;
}
