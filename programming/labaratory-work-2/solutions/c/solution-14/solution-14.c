#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int* numbers = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf_s("%d", &numbers[i]);
    }

    int i = 0;

    do {
        i++;
    } while (numbers[i - 1] >= 0 && numbers[i - 1] > numbers[i]);

    if (i > 1 && numbers[i - 1] < 0) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}