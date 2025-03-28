#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int n;

	do {
		printf("������� ����������� ������� (4 <= n <= 10): ");
		scanf_s("%d", &n);
	} while (n < 4 || n > 10);

	int matrix[10][10] = { 0 };
	int degrees[10] = { 0 };

	printf("������� ���������:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 2;
			degrees[i] += matrix[i][j];
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	int max = 0;
	int vertex = 0;

	for (int i = 0; i < n; i++) {
		if (degrees[i] > max) {
			max = degrees[i];
			vertex = i;
		}
	}

	printf("������� � ������������ ������������ ������: %d\n", vertex + 1);
	printf("��������� ��� ��� ������� %d: {", vertex + 1);
	for (int j = 0; j < n; j++) {
		if (matrix[vertex][j] == 1) {
			printf(" (%d, %d) ", vertex + 1, j + 1);
		}
	}
	printf("}\n");

	return 0;
}