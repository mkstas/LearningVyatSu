#include <stdio.h>
#include <math.h>

int main()
{
    int K, n;
    scanf("%d %d", &K, &n);

    if (K > pow(2, n - 1) - 1 || K < (pow(2, n - 1) - 1) * -1) {
        printf("Ошибка");
        return 0;
    }

    printf("%d", K < 0 ? 1 : 0);

    K = abs(K);

    for (int i = n - 2; i >= 0; i--) {
        printf("%d", K >> i & 1);
    }

    return 0;
}