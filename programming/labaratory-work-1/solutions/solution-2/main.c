#include <stdio.h>

int main() {
  int n = 0;
  int m = 0;
  int sum = 0;

  scanf_s("%d", &n);
  scanf_s("%d", &m);

  for (int i = 0; i < m; i++) {
    sum += n % 10;
    n /= 10;
  }

  printf_s("%d", sum);

  return 0;
}