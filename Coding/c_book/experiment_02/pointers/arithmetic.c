#include <stdio.h>

void strcopy(char *s, char *t){
    while ((*s++ = *t++)){
        ;
    }
}

void strn_copy(char *s, char *t, int n)
{ /*Copy at most n characters from t to s, version without padding when smaller with '\0'. */
    while (n-- > 0 && (*s++ = *t++))
        ;
}

int str_compare(char *s, char *t){
    for (; *s == *t; s++, t++){
        if (*s == '\0'){
            return 0;}}
    return *s - *t;
}

void str_cat(char *s, char *t)
{/*Copy t at the end of s.*/
    while (*s)
        s++;

    while ((*s++ = *t++))
        ;
}

void strn_cat(char *s, char *t, int n){
    while (*s)
        s++;
    while (n-- > 0 && *t)
        *s++ = *t++;
    *s = '\0'; /* Need to always null-terminate if t is long. */
}

int strend(char *s, char *t)
{/* Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise. */
    char *bs = s;
    char *bt = t;

    while (*s)
        s++;

    while (*t)
        t++;

    if (t == bt)
        return 1;

    while (s > bs && t > bt && *--s == *--t)
        ;

    return t == bt && *s == *t;
}

int main(){
    char s[20] = "aaa";
    char t[] = "iiiiiiiii";

    str_cat(s, t);
    printf("%s\n", s);

    // strcopy(s, t);
    // printf("%s\n", s);

    return 0;
}
