#include <stdio.h>

int main() {
  int n = 0;

  scanf_s("%d", &n);

  int eng = 0;
  int ger = 0;
  int fra = 0;

  for (int i = n; i > 0; i--) {
    int ans = 0;

    scanf_s("%d", &ans);

    switch (ans) {
    case 1:
      eng++;
      break;

    case 2:
      ger++;
      break;

    case 3:
      fra++;
      break;
    }
  }

  printf_s("%d %d %d", eng, ger, fra);

  return 0;
}