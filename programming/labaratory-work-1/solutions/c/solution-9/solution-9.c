#include <stdio.h>

int main()
{
    int n, m;

    scanf_s("%d %d", &n, &m);

    int count = 0;

    for (int i = n; i <= m; i++) {
        int a = i % 10;
        int b = i / 10 % 10;
        int c = i / 100 % 10;
        int d = i / 1000 % 10;
        int e = i / 10000 % 10;
        int f = i / 100000 % 10;

        if ((a + b + c) == (d + e + f))
            count++;
    }

    printf("%d", count);

    return 0;
}