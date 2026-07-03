#include <stdio.h>

void input_to_output(){
    int c;
    c = getchar();
    while (c != EOF){
        putchar(c);
        c = getchar();
    }
}
void input_to_output_bis(){
    int c;
    while ((c = getchar()) != EOF){
        putchar(c);
    }
}

void exercise(){
    int result;
    while ((result = (getchar() != EOF)) != 0){
        printf("%d\n", result);
    }
    printf("%d\n", result);
}

int main(){
    exercise();
}