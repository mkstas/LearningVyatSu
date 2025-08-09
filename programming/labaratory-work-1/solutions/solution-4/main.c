#include <stdio.h>

int main() {
  int n = 0;
  int min_n = 0;
  int min_i = 0;

  for (int i = 1; n != 0 || i == 1; i++) {
    scanf_s("%d", &n);

    if ((n < min_n || i == 1) && n != 0) {
      min_n = n;
      min_i = i;
    }
  }

  printf_s("%d", min_i);

  return 0;
}