#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter size of array\n");
    scanf("%d", &n);
    //int A[n];
    int *A = (int*)malloc(n*sizeof(int));
    for (int i = 0; i<n; i++){
        A[i] = i+1;
    }
    int* B = (int*)realloc(A, 2*n*sizeof(int)); /*realloc follows same initialization to zero as calloc does.*/
    for (int i = 0; i<2*n; i++){
        printf("%d ", B[i]);
    }
    printf("\n");
}