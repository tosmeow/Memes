#include <stdio.h>

void dereferencing(){
    int c;
    int *p;
    p = &c;
    c = 1;
    printf("%d\n", c);
    printf("%d\n", *p);
}

void increments(){
    int c;
    int *p;
    c = 0;
    p = &c;
    printf("%d\n", *p);
    printf("%d\n", c);
    // p++;
    // printf("%d\n", *p);
    // printf("%d\n", c);
    (*p)++;
    printf("%d\n", *p);
    printf("%d\n", c);
}

void array_pointers(){
    int val[5], i;
    int *p, v;
    for (i=0; i<5; i++){
        val[i] = i;
    }
    p = &val[0];
    for (i=0; i<5; i++){
        printf("%d\n", *p);
        p++;
    }
    for (i=0; i<5; i++){
        printf("%d\n", val[i]);
    }
    v = (val == &val[0]); /*The array is a pointer to the first indexed value of itself? exceot for operations that treat it like a variable.*/
    printf("%d\n", v);
    // printf("%d\n", val[-1]);
}

int str_len(char *s){
    int n;
    for (n = 0; *s != '\0'; s++){
        n++;}
    return n;
}

int main(){
    array_pointers();
}