#include <stdio.h>

int main() {
    int N; 
    scanf("%d", &N);

    int a = N % 10;
    int b = N / 10 % 10;
    N /= 100;

    int max = a;
    int min = a;

    if (b > max && b > N) {
        max = b;
    } else if (N > max && N > b) {
        max = N;
    }

    if (b < min) {
        min = b;
    } else if (N < min) {
        min = N;
    }

    if ((max + min) / 2 < a + b + N - max - min) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}