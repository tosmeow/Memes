#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
static int sp = 0;
static double val[MAXVAL];
void push(double f){
    if (sp < MAXVAL){
        val[sp++] = f;
    }
    else {
        printf("Error: Stack is full, can't push\n");
    }
}

double pop(void){
    if (sp > 0){
        return val[--sp];
    }
    else {
        printf("Error: Can't pop, stack empty.");
        return 0.0;
    }
}