#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    int nums[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &nums[i]);
    }

    int i = 0;

    do {
        i++;
    } while (nums[i - 1] >= 0 && nums[i - 1] > nums[i]);

    if (i > 1 && nums[i - 1] < 0) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}