#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int q = ceil(log2(n));

    for (int i = 0; i < n; i++) {
        for (int j = q - 1; j >= 0; j--) {
            printf("%d", i >> j & 1);
        }
        printf(" ");
    }

    return 0;
}