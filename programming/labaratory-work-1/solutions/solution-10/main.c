#include <stdio.h>

int main() {
  int m = 0;

  scanf_s("%d", &m);

  int good_group = 0;
  int n_skip = 0;
  float avg_skip = 0.0;

  for (int i = 0; i < m; i++) {
    float k = 0;
    float sum_skip = 0;

    scanf_s("%d", &k);

    for (int j = 0; j < k; j++) {
      scanf_s("%d", &n_skip);

      sum_skip += n_skip;
    }

    avg_skip = sum_skip / k;

    if (avg_skip < 10 && good_group == 0) {
      good_group = i;
    }
  }

  if (good_group != 0) {
    printf_s("The good group %d", good_group);

    return 0;
  }

  printf_s("No");

  return 0;
}