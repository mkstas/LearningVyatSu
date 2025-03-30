#include <stdio.h>

int main()
{
    int k, m, n;

    scanf_s("%d %d %d", &k, &m, &n);

    int count = 0;

    for (int i = 0; i < n; i++) {
        count += k >> i & 1 ^ m >> i & 1;
    }

    printf("%d", count);

    return 0;
}