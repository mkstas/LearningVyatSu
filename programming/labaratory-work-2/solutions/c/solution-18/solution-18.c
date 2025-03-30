#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int* numbers = (int*)malloc(sizeof(int) * n + sizeof(int) * 2);

    for (int i = 1; i <= n; i++)
        scanf_s("%d", &numbers[i]);

    int countOdd = 0;
    float countEven = 0;
    float sumEven = 0;

    for (int i = 1; i <= n; i++) {
        if (numbers[i] % 3 == 0)
            countOdd++;

        if (numbers[i] % 2 == 0) {
            sumEven += numbers[i];
            countEven++;
        }
    }

    numbers[0] = countOdd;
    numbers[n + 1] = rint(sumEven / countEven);

    for (int i = 0; i <= n + 1; i++)
        printf("%d ", numbers[i]);

    return 0;
}