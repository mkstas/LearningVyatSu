#include <stdio.h>
#include <math.h>

int main()
{
    int N;
    scanf("%d", &N);
    int numbers[N + 2];

    for (int i = 1; i <= N; i++) {
        scanf("%d", &numbers[i]);
    }

    int cntOdd = 0;
    float cntEven = 0;
    float sumEven = 0;

    for (int i = 1; i <= N; i++) {
        if (numbers[i] % 3 == 0) {
            cntOdd++;
        }
        if (numbers[i] % 2 == 0) {
            sumEven += numbers[i];
            cntEven++;
        }
    }

    numbers[0] = cntOdd;
    numbers[N + 1] =  rint(sumEven / cntEven);

    for (int i = 0; i <= N + 1; i++) {
        printf ("%d ", numbers[i]);
    }

    return 0;
}