#include <stdio.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int count = 0;
    int prevK = 0;

    for (int i = 0; i < n; i++) {
        int k;

        scanf_s("%d", &k);

        if (k > 0 && prevK < 0 || k < 0 && prevK > 0)
            count++;

        prevK = k;
    }

    printf("%d", count);

    return 0;
}