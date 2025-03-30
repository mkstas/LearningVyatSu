#include <stdio.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int count = 0;

    do {
        count += ~n & 1, n >>= 1;
    } while (n);

    printf("%d", count);

    return 0;
}