#include <stdio.h>

void count_incr();
void temperatures_count();


int main()
{
    temperatures_count();
}
/* Below is the core where the actual functions are defined */
void count_incr()
{
    int count;
    for (count = 0; count <= 10; ++count)
        printf("%d\t", count);
    printf("\n");
}

void temperatures_count()
{
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, 5.0 / 9.0 * (fahr - 32));
}