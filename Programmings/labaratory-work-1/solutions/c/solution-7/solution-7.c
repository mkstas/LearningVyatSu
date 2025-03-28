#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    int cnt = 0;
    int prev_k = 0;

    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);

        if (k > 0 && prev_k < 0 || k < 0 && prev_k > 0) {
            cnt++;
        }
        prev_k = k;
    }

    printf("%d", cnt);

    return 0;
}