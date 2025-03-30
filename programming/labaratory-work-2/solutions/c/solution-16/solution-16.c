#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int n1[N], n2[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &n1[i]);
    }

    int j = 0;

    for (int i = 1; i < N; i++) {
        if (n1[i - 1] < n1[i]) {
            n2[j] = n1[i - 1];
            j++;
        }
    }

    if (j > 0) {
        printf("%d\n", j);

        for (int i = 0; i < j; i++) {
            printf("%d ", n2[i]);
        }
    } else {
        printf("NO");
    }

    return 0;
}