#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int nums[N];
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &nums[i]);
    }

    int zeros = 0;
    int sum = 0;

    do {
        N--;
        if (nums[N] == 0) {
            zeros++;
        }
        if (zeros == 1) {
            sum += nums[N];
        }
    } while (zeros < 2);

    printf("%d", sum);

    return 0;
}