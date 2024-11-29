#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int n_cpy = n, cnt = 0;
    while (n_cpy) cnt++, n_cpy >>= 1;

    for (int i = 0; i < n; i++) {
        for (int j = cnt - 1; j >= 0; j--) {
            printf("%d", i >> j & 1);
        }
        printf(" ");
    }

    return 0;
}