#include <stdio.h>
#include <math.h>

int main()
{
    int k, n;

    scanf_s("%d %d", &k, &n);

    if (k < 0 || k > pow(2, n) - 1) {
        printf("Error");

        return 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        printf("%d", k >> i & 1);
    }

    return 0;
}