#include <stdio.h>

int main()
{
    int N, cnt = 0;
    scanf("%d", &N);

    do {
        cnt += ~N & 1, N >>= 1;
    } while (N);

    printf("%d", cnt);

    return 0;
}