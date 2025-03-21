#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int n;

	do {
		printf("¬ведите размерность матрицы (4 <= n <= 10): ");
		scanf_s("%d", &n);
	} while (n < 4 || n > 10);

	srand(time(NULL));

	int* outNodes = (int*)malloc(sizeof(int) * n);
	int** matrix = (int*)malloc(sizeof(int) * n * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * n);
	}

	printf("ћатрица смежности размерностью %d\n", n);
	for (int i = 0; i < n; i++) {
		outNodes[i] = 0;
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 2;
			printf("%d ", matrix[i][j]);
			outNodes[i] += matrix[i][j];
		}
		printf("\n");
	}

	int max = outNodes[0];
	int vertex = 0;
	for (int i = 1; i < n; i++) {
		if (outNodes[i] > max) {
			max = outNodes[i];
			vertex = i + 1;
		}
	}

	printf("¬ершина с максимальной полустепенью исхода: %d\n", vertex);

	for (int i = 0; i < n; i++) {
		if (matrix[vertex][i] == 1) {
			printf("(%d -> %d)\n", vertex, i);
		}
	}

	return 0;
}