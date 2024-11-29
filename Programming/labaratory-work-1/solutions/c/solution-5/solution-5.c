#include <stdio.h>

int main() {
    int A;
    int B;
    int x;
    int y;
    int z;
    scanf("%d %d %d %d %d", &A, &B, &x, &y, &z);

    if (x * z <= A * B || y * z <= A * B || x * y <= A * B) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}