#include <stdio.h>
#include <math.h>

int main()
{
    int k, n;

    scanf_s("%d %d", &k, &n);

    if (k > pow(2, n - 1) - 1 || k < (pow(2, n - 1) - 1) * -1) {
        printf("Error");

        return 0;
    }

    printf("%d", k < 0 ? 1 : 0);

    k = abs(k);

    for (int i = n - 2; i >= 0; i--)
        printf("%d", k >> i & 1);

    return 0;
}