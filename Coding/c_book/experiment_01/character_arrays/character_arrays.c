#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */
int get_line(FILE *input, char line[], int maxline);
void copy(char to[], char from[]);

int main(){
    int len, max;
    char line[MAXLINE], longest[MAXLINE];
    FILE *input;

    input = stdin;
    max = 0;
    while ((len = get_line(input, line, MAXLINE)) > 0){
        if (len > max){
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0){
        printf("%s", longest);
    }
    return 0;
}

/* get_line: read one line from input into s, return length */
int get_line(FILE *input, char s[],int lim){
    int c, i;
    for (i=0; i < lim-1 && (c=fgetc(input))!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]){
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
