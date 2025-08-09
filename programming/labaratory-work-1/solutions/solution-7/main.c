#include <stdio.h>

int main() {
  int n = 0;

  scanf_s("%d", &n);

  int count = 0;
  int prev_k = 0;

  for (int i = 0; i < n; i++) {
    int k = 0;

    scanf_s("%d", &k);

    if (k > 0 && prev_k < 0 || k < 0 && prev_k > 0) {
      count++;
    }

    prev_k = k;
  }

  printf_s("%d", count);

  return 0;
}