#include <stdio.h>

void count_occurences(){
    int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;
    for (i=0; i < 10; ++i)
        ndigit[i] = 0;
    while ((c = getchar()) != EOF){
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    }
    printf("Digits appearance rate was:\n");
    for (i = 0; i < 10; ++i)
        printf("%d appeared %d times\n", i, ndigit[i]);
    printf("Meanwhile, remaining appearances were\n");
    printf("-White space = %d\n-other = %d\n", nwhite, nother);
}

int main(){
    count_occurences();
}