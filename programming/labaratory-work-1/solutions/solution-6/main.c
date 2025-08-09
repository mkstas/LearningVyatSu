#include <stdio.h>

int main() {
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
  int s = 0;

  scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);

  if (x1 < 0) {
    x1 = 0;
  }

  if (y1 < 0) {
    y1 = 0;
  }

  if (x2 < 0) {
    x2 = 0;
  }

  if (y2 < 0) {
    y2 = 0;
  }

  s = (x1 - x2) * (y1 - y2);

  if (s < 0) {
    s *= -1;
  }

  printf("%d", s);

  return 0;
}