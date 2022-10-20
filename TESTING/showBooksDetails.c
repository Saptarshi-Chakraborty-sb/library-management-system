#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define __DATA_FOLDER ".LMS_DATA"
#define __DATA_STUDENTS_FILE ".LMS_DATA\\STUDENTS.txt"
#define __DATA_BOOKS_FILE ".LMS_DATA\\BOOKS.txt"
#define __DATA_ISSUE_FILE ".LMS_DATA\\ISSUE.txt"

int strpos(char *, char);

void main()
{
    FILE *bookFile;
    char line[200], ch = 'c', bID[10], name[70], author[70], publication[50], noOfCopies[3], date[12], time[8];
    int count, length, commaPos, prevPos;

    bookFile = fopen(__DATA_BOOKS_FILE, "r");
    
    system("cls");

    // Checks if the file is Empty
    if (fgetc(bookFile) == EOF)
    {
        printf("\t--- No Books Data Found ---\n");
        return;
    }
    fseek(bookFile, 0, SEEK_SET);

    printf("\t\t  --- ALL BOOKSS DETAILS ---\n\n");
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
        printf(" %30s |", author);
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

    printf("\n---------------------------\n");

    fclose(bookFile);
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