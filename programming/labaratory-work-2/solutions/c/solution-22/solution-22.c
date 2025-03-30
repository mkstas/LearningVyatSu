#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    float* numbers = (int*)malloc(sizeof(float) * n);

    for (int i = 0; i < n; i++)
        scanf_s("%f", &numbers[i]);

    int i = 1;

    while (numbers[i - 1] <= numbers[i])
        i++;

    if (i == n)
        printf("%d", 0);
    else
        printf("%d", i);

    return 0;
}