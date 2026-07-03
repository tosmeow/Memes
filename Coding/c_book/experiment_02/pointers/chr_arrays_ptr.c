#include <stdio.h>

#include <string.h>

void creation(){
    char c[10];
    c[0] = 'J';
    c[1] = 'O';
    c[2] = 'H';
    c[3] = 'N';
    c[4] = '\0';
    printf("%s", c);
}

void creation_missized(){
    char c[10];
    c[0] = 'J';
    c[1] = 'O';
    c[2] = 'H';
    c[3] = 'N';
    printf("%s", c);
}

void test(){
    char c[5] = "JOHN";
    printf("Size in bytes = %zu\n", sizeof(c));
    size_t len = strlen(c);
    printf("Length = %zu\n", len);
}

/* Arrays (and so string thereof) are always passed as references in function arguments. */

/* Unlike in the C videos, now sizeof and strlen eg. are returning the sizes as size_t objects
and not as int, as such you need zu as appropriate print specifier instead of %d.*/


/* If size is larger and not fully filled, it will not print correctly just JOHN but have ???? on the undefined left fields; however if we do finish off with \0*/
/*The string length is becoming the final part where had \0 last.*/

void print(char* c){
    int i = 0;
    while (c[i] != '\0'){
        printf("%c", c[i]);
        i++;
    }
    printf("\n");
}

void print_ptr(char* c){
    while (*c != '\0'){
        printf("%c", *c);
        c++;
    }
    printf("\n");
}

void print_pointers(char *c){
    while (*c != '\0'){
        printf("%p\n", c);
        c++;
    }
}




int main(){
    char *c = "Hello";
    print_pointers(c);
    print_ptr(c);
}
