#include <stdio.h>

int main() {
    int N, i;
    scanf("%d %d", &N, &i);
    printf("%d", N >> i & 1);

    return 0;
}