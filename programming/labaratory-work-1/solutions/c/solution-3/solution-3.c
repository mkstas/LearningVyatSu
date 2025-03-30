#include <stdio.h>

int main()
{
    int n;

    scanf_s("%d", &n);

    int a = n % 10;
    int b = n / 10 % 10;
    int max = a;
    int min = a;

    n /= 100;

    if (b > max && b > n) {
        max = b;
    } else if (n > max && n > b) {
        max = n;
    }

    if (b < min) {
        min = b;
    } else if (n < min) {
        min = n;
    }

    if ((max + min) / 2 < a + b + n - max - min) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}