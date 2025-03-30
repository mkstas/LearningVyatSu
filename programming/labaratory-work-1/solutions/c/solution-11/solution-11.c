#include <stdio.h>

int main() {
    float k1, b1, k2, b2, e;
    scanf("%f %f %f %f %f", &k1, &b1, &k2, &b2, &e);

    if (k1 == k2) {
        printf("No");
    } else {
        float x = (b2 - b1) / (k1 - k2);
        float y = k1 * x + b1;

        if (x * x + y * y <= e * e) {
            printf("Yes");
        } else {
            printf("No");
        }
    }
    return 0;
}