#include <stdio.h>
#include <math.h>

void printBin(int n, int b)
{
    for (int i = b - 1; i >= 0; i--) {
        printf("%d", n >> i & 1);
    }
}

int main()
{
    float x;
    int n, k;

    scanf_s("%f %d %d", &x, &n, &k);

    int* d = (int*)&x;
    int s = *d >> 31;
    int e = *d >> 23 & (int)pow(2, 8) - 1;
    int m = *d & (int)pow(2, 23) - 1;
    int p = e - (pow(2, 7) - 1);
    int c = p + 1 + pow(2, n - k - 2);

    if (k < 23) {
        e = p + (pow(2, n - k - 2) - 1);

        if (p > 0) {
            m = m / pow(2, k + p);
        } else {
            m = m / pow(2, 23 - k);
        }
    }

    printBin(s, 1);
    printBin(e, n - k - 1);
    printBin(m, k);
    printf("\n");

    m = (m + pow(2, k)) / 2;

    printBin(s, 1);
    printBin(m, k);
    printf("%d", p + 1 < 0 ? 1 : 0);
    printBin(abs(p + 1), n - k - 2);
    printf("\n");

    printBin(s, 1);
    printBin(m, k);
    printBin(c, n - k - 1);
    printf("\n");

    return 0;
}