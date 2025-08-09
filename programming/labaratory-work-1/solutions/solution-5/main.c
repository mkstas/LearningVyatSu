#include <stdio.h>

int main() {
  int a = 0;
  int b = 0;
  int x = 0;
  int y = 0;
  int z = 0;

  scanf_s("%d %d %d %d %d", &a, &b, &x, &y, &z);

  if (x * z <= a * b || y * z <= a * b || x * y <= a * b) {
    printf_s("Yes");

    return 0;
  }

  printf_s("No");

  return 0;
}