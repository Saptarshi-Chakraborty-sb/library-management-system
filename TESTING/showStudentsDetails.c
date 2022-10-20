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
    FILE *studentFile;
    char line[60], ch = 'c', sID[10], name[30], class[2], section[1], roll[3], year[4];
    int count, length, commaPos, prevPos;

    studentFile = fopen(__DATA_STUDENTS_FILE, "r");

    // Checks if the file is Empty
    if (fgetc(studentFile) == EOF)
    {
        printf("\t--- No Student Data Found ---\n");
        return;
    }
    fseek(studentFile, 0, SEEK_SET);

    system("cls");
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

    printf("\n---------------------------\n");

    fclose(studentFile);
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

