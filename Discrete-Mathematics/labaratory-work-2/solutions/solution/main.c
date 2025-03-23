#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void printTableHead(int n)
{
	printf("Матрица смежности\n    ");
	for (int i = 0; i < n; i++) {
		printf("%d  ", i + 1);
	}
	printf("\n    ");

	for (int i = 0; i < n - 1; i++) {
		printf("----");
	}
	printf("\n");
}

void generateAndPrintMatrix(int n, int** matrix)
{
	for (int i = 0; i < n; i++) {
		printf(" %d |", i + 1);
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 2;
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void findDegree(int n, int** matrix, int* degrees)
{
	for (int i = 0; i < n; i++) {
		degrees[i] = 0;
		for (int j = 0; j < n; j++) {
			degrees[i] += matrix[i][j];
		}
	}
}

int findVertexWithMaxDegree(int n, int* degrees)
{
	int max = degrees[0];
	int vertex = 0;

	for (int i = 0; i < n; i++) {
		if (degrees[i] > max) {
			max = degrees[i];
			vertex = i + 1;
		}
	}

	printf("Вершина с максимальной полустепенью исхода: %d\n", vertex);
	return vertex;
}

void find_edges_from_vertex(int n, int** matrix, int vertex) {
    printf("Рёбра, исходящие из вершины %d: ", vertex);
    for (int i = 0; i < n; i++) {
        if (matrix[vertex][i] == 1) {
            printf("(%d -> %d) ", vertex, i + 1);
        }
    }
    printf("\n");
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int n, vertex = 0;

	do {
		printf("Введите размерность матрицы (4 <= n <= 10): ");
		scanf_s("%d", &n);
	} while (n < 4 || n > 10);

	int** matrix = (int*)malloc(sizeof(int) * n * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * n);
	}
	int* degrees = (int*)malloc(sizeof(int) * n);

	printTableHead(n);
	generateAndPrintMatrix(n, matrix);
	findDegree(n, matrix, degrees);
	vertex = findVertexWithMaxDegree(n, degrees);
	find_edges_from_vertex(n, matrix, vertex);

	return 0;
}