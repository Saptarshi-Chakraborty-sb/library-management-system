#include <stdio.h>


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