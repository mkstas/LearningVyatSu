#include <stdio.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int prevK = 0;
    int count = 0;
    int maxCount = 0;

    for (int i = 0; i < n; i++) {
        int k;

        scanf_s("%d", &k);

        if (k <= prevK) {
            count = 1;
        } else {
            count++;
        }

        if (count > maxCount) {
            maxCount = count;
        }

        prevK = k;
    }

    printf("%d", maxCount);

    return 0;
}