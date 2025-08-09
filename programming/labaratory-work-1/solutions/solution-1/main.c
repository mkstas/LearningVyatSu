#include <stdio.h>

int main() {
  int n = 0;

  scanf_s("%d", &n);

  int prev_k = 0;
  int count = 0;
  int max_count = 0;

  for (int i = 0; i < n; i++) {
    int k = 0;

    scanf_s("%d", &k);

    if (k > prev_k) {
      count++;
    }

    if (k <= prev_k) {
      count = 1;
    }

    if (count > max_count) {
      max_count = count;
    }
  }

  printf_s("%d", max_count);

  return 0;
}