#include <stdio.h>

void implicit_def(){
    int i;
    i = 0;
    // uwupapi(); 
    /* This test here confirms that implicit function definition does not work in C anymore.
    It now raises an error. */
}

void local_blocks(){
    int i, j;
    printf("%d\n", j);
    {int j;
    j=0;
    j++;
    printf("%d\n", j);} /* The changes to j here are only done locally it seems? */
    printf("%d\n", j);
}

int main(){
    local_blocks();
}