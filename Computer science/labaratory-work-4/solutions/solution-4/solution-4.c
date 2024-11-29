#include <stdio.h>

int main() {
    int K, M, n;
    scanf("%d %d %d", &K, &M, &n);

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        cnt += K >> i & 1 ^ M >> i & 1;
    }

    printf("%d", cnt);

    return 0;
}