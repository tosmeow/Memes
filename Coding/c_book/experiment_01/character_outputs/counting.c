#include <stdio.h>

#define IN 1
#define OUT 0

void count(){
    long nc;
    nc = 0;
    while (getchar() != EOF){
        ++nc;
    }
    printf("%ld\n", nc);
}

void count_bis(){
    double nc;
    for (nc = 0; getchar() != EOF; nc++)
        ;
    printf("%.0f\n", nc);
}

void line_counting(){
    int c, nl;
    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}

void word_counting(){
    int c, nl, nc, nw, state;
    state = OUT;
    nw = nl = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

int main(){
    word_counting();
}
