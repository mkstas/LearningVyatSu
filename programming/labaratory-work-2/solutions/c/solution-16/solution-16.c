#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int* n1 = (int*)malloc(sizeof(int) * n);
    int* n2 = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf_s("%d", &n1[i]);
    }

    int j = 0;

    for (int i = 1; i < n; i++) {
        if (n1[i - 1] < n1[i]) {
            n2[j] = n1[i - 1];
            j++;
        }
    }

    if (j > 0) {
        printf("%d\n", j);

        for (int i = 0; i < j; i++) {
            printf("%d ", n2[i]);
        }
    } else {
        printf("NO");
    }

    return 0;
}