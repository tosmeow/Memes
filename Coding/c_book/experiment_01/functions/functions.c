#include <stdio.h>
#define BASE 2
#define MAX 31

int power(int, int);

int main(){
    int i;
    for (i=1; i <= MAX; ++i){
        printf("%d-th power of %d is %d.\n", i, BASE, power(BASE, i));
    }
}

int power(int base, int n){
    int i, p;
    p = base;
    for (i = 1; i <= n; ++i){
        p = p * base;
    }
    return p;
}