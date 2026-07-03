#include <stdio.h>

void hello(){
    printf("hello, world\n");
}

void temperatures(){
    int low, up, step;
    int fahr, celsius;

    low = 0;
    up = 300;
    step = 20;

    fahr = low;
    while (fahr <= up){
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void temperatures_aligned(){
    int low, up, step;
    int fahr, celsius;

    low = 0;
    up = 300;
    step = 20;

    fahr = low;
    while (fahr <= up){
        celsius = 5 * (fahr - 32) / 9;
        printf("%3d %6d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void temperatures_aligned_f64(){
    int low, up, step;
    float fahr, celsius;

    low = 0;
    up = 300;
    step = 20;

    fahr = low;
    while (fahr <= up){
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

int main()
{
    temperatures_aligned_f64();
}