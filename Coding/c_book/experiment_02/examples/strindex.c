#include <stdio.h>

/*Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none.*/

int charindex(char s[], char t){
    int i,j;
    i = 0;
    j = -1;
    while (s[i] != '\0'){
        if (s[i] == t){
            j = i;
        }
        i++;
    }
    return j
}

int strindex(char s[], char t[])
{
    int i, j, k;
    int pos;

    pos = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;

        if (k > 0 && t[k] == '\0')
            pos = i;
    }

    return pos;
}