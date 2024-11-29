#include <stdio.h>
#include <math.h>

int main() {
    int K, n;
    scanf("%d %d", &K, &n);

    if (K > pow(2, n - 1) - 1 || K < (pow(2, n - 1) - 1) * -1) {
        printf("Ошибка");
        return 0;
    }

    if (K < 0) {
        K = abs(K);
        K = ~K;
    }

    for (int i = n - 1; i >= 0; i--) {
        printf("%d", K >> i & 1);
    }

    return 0;
}