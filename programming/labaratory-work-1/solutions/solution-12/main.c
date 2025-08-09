#include <stdio.h>

int main() {
  int n = 0;

  scanf_s("%d", &n);

  int sum = 0;

  for (int i = 1; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }

  if (sum == n) {
    printf_s("Yes");

    return 0;
  }

  printf_s("No");

  return 0;
}