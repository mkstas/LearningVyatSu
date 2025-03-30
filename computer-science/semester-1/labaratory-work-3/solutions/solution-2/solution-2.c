#include <stdio.h>

int main()
{
    int n, i;

    scanf_s("%d %d", &n, &i);
    printf("%d", n >> i & 1);

    return 0;
}