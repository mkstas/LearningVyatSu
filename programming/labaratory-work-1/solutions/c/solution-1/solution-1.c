#include <stdio.h>

int main() {
    int N; 
    scanf("%d", &N);

    int prev_k = 0;
    int cnt = 0;
    int max_cnt = 0;

    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);

        if (k <= prev_k) {
            cnt = 1;
        } else {
            cnt++;
        }

        if (cnt > max_cnt)
        {
            max_cnt = cnt;
        }

        prev_k = k;
    }

    printf("%d", max_cnt);

    return 0;
}