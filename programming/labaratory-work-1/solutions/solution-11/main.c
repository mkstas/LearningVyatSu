#include <stdio.h>

int main() {
  float k1 = 0.0;
  float b1 = 0.0;
  float k2 = 0.0;
  float b2 = 0.0;
  float e = 0.0;

  scanf_s("%f %f %f %f %f", &k1, &b1, &k2, &b2, &e);

  if (k1 == k2) {
    printf_s("No");

    return 0;
  }

  float x = (b2 - b1) / (k1 - k2);
  float y = k1 * x + b1;

  if (x * x + y * y <= e * e) {
    printf_s("Yes");

    return 0;
  }

  printf_s("No");

  return 0;
}