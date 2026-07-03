#include <stdio.h>

#define ARRAY_SIZE 10

void quick_sort(int v[], int left, int right);
void swap(int v[], int i, int j);
void print_array(int v[], int len);

int main(void)
{
    int values[ARRAY_SIZE] = {8, 3, 5, 1, 9, 2, 7, 4, 6, 0};

    print_array(values, ARRAY_SIZE);
    quick_sort(values, 0, ARRAY_SIZE - 1);
    print_array(values, ARRAY_SIZE);

    return 0;
}

void quick_sort(int v[], int left, int right)
{
    int i;
    int last;

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    quick_sort(v, left, last - 1);
    quick_sort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void print_array(int v[], int len)
{
    int i;

    for (i = 0; i < len; i++) {
        printf("%d", v[i]);

        if (i < len - 1) {
            printf(" ");
        }
    }

    printf("\n");
}
