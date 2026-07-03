#include <stdio.h>

void operator(){
    int a[5] = {2,4,6,8,10}; /* Creates a contiugous sequence of memory in the machine: addresses p, p+4,..., p+16 if integers take 4 bytes & starts at address p (stored as a hexadecimal integer.)*/
    int *p = a;
    printf("%p\n", p);
    printf("%d\n", *p);
    printf("%d\n", *(p+2));
}

void md_array(){
    int b[2][3]; /*Creating 2 1D arrays of 3 integers. */
    /*At address b, the first 4*3 bytes correspond to the 1D array b[0], then the following 12 correspond to b[1].*/
    /*int *p = b; Compile error: returns a pointer to a pointer of integers.*/
    int (*p)[3] = b;
    printf("%p\n", b);
}

int main(){
    md_array();
}