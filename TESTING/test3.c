#include <stdio.h>
void main()
{
    char sentence[10];
    printf("Hello World\n");
    printf("Enter a string\n");

    // gets(sentence);
    fgets(sentence, 10, stdin);

    printf("String is [%s]\n", sentence);
}