#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int* numbers = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        scanf_s("%d", &numbers[i]);

    int zeros = 0;
    int sum = 0;

    do {
        n--;
        if (numbers[n] == 0)
            zeros++;
        if (zeros == 1)
            sum += numbers[n];
    } while (zeros < 2);

    printf("%d", sum);

    return 0;
}