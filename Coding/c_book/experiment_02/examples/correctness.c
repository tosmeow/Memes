#include <stdio.h>
#include <math.h>

void sqrt_correctness(){
    int n;
    float root, int_root;
    n = 4;
    root = sqrt(n);
    int_root = sqrt((double) n);
    printf("%f\n", root);
    printf("%f\n", int_root);
}

int maximum(int a, int b){
    int z;
    z = (a > b) ? a : b;
    return z;
}

int main(){
    int a, b, c;
    a = 1;
    b = 2;
    c = maximum(a, b);
    printf("%d\n", c);
}