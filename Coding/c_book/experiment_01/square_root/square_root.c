#include <stdio.h>
#define MAX_DIGIT 6
#define TARGET 42
int main(){
    int precision;
    double c, root, digit;
    c = TARGET;
    root = 0;
    digit = 1.0;
    for (precision = 0; precision < MAX_DIGIT;  precision = precision + 1){
        while (root * root < c){
            root = root + digit;
        }
        root = root - digit;
        digit = digit / 10.0;
        printf("Intermediate root is %.*f of %f with current square equal to %f\n", precision, root, c, root * root);
    }
}