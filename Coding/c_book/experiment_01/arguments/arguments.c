#include <stdio.h>

void arr_modifier(int*);
void loop_array();
void arg_modifier(int);
void loop_arg();

int main(){
    loop_arg();
}

void loop_array(){
    int i, arr[10];
    for (i=0; i < 10; ++i){
        arr[i] = 0;
    }
    arr_modifier(arr);
    for (i=0; i<10; ++i){
        printf("%d\n", arr[i]);
    }
}

void arr_modifier(int* arr){
    arr[0] = 1;
}

void loop_arg(){
    int i;
    i=0;
    arg_modifier(i);
    printf("%d\n", i);
}

void arg_modifier(int n){
    n = 1;
}
