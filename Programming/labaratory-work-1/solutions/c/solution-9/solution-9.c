#include <stdio.h>

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    int cnt = 0;

    for (int i = N; i <= M; i++) {
        int a = i % 10;
        int b = i / 10 % 10;
        int c = i / 100 % 10;
        int d = i / 1000 % 10;
        int e = i / 10000 % 10;
        int f = i / 100000 % 10;

        if ((a + b + c) == (d + e + f)) {
            cnt++;
        }
    }

    printf("%d", cnt);

    return 0;
}