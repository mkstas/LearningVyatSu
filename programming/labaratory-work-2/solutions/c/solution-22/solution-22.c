#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    float nums[N];

    for (int i = 0; i < N; i++) {
        scanf("%f", &nums[i]);
    }

    int i = 1;

    while (nums[i - 1] <= nums[i]) {
        i++;
    }

    if (i == N) {
        printf("%d", 0);
    } else {
        printf("%d", i);
    }

    return 0;
}