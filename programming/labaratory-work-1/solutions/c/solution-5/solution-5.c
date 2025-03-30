#include <stdio.h>

int main()
{
    int A, B, x, y, z;

    scanf_s("%d %d %d %d %d", &A, &B, &x, &y, &z);

    if (x * z <= A * B || y * z <= A * B || x * y <= A * B) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}