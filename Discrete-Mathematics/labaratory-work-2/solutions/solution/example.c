//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define MAX_N 10
//#define MIN_N 4
//
//// Функция для генерации случайной матрицы смежности для орграфа
//void generate_adjacency_matrix(int adj_matrix[MAX_N][MAX_N], int n) {
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            adj_matrix[i][j] = rand() % 2; // случайное значение 0 или 1
//        }
//    }
//}
//
//// Функция для нахождения полустепени исхода каждой вершины
//void find_out_degree(int adj_matrix[MAX_N][MAX_N], int n, int out_degrees[MAX_N]) {
//    for (int i = 0; i < n; i++) {
//        out_degrees[i] = 0;
//        for (int j = 0; j < n; j++) {
//            out_degrees[i] += adj_matrix[i][j]; // Суммируем элементы в строке для вершины i
//        }
//    }
//}
//
//// Функция для поиска вершины с максимальной полустепенью исхода
//int find_vertex_with_max_out_degree(int out_degrees[MAX_N], int n) {
//    int max_out_degree = out_degrees[0];
//    int vertex = 0;
//    for (int i = 1; i < n; i++) {
//        if (out_degrees[i] > max_out_degree) {
//            max_out_degree = out_degrees[i];
//            vertex = i;
//        }
//    }
//    return vertex;
//}
//
//// Функция для вывода рёбер, исходящих из вершины
//void find_edges_from_vertex(int adj_matrix[MAX_N][MAX_N], int n, int vertex) {
//    printf("Рёбра, исходящие из вершины %d: ", vertex);
//    for (int i = 0; i < n; i++) {
//        if (adj_matrix[vertex][i] == 1) {
//            printf("(%d -> %d) ", vertex, i);
//        }
//    }
//    printf("\n");
//}
//
//int main() {
//    srand(time(NULL)); // Инициализация генератора случайных чисел
//
//    int n;
//    printf("Введите размерность матрицы (4 <= n <= 10): ");
//    scanf("%d", &n);
//
//    // Проверка на допустимый диапазон
//    while (n < MIN_N || n > MAX_N) {
//        printf("Размерность должна быть от 4 до 10. Введите снова: ");
//        scanf("%d", &n);
//    }
//
//    int adj_matrix[MAX_N][MAX_N];  // Матрица смежности
//    int out_degrees[MAX_N];         // Массив для хранения полустепени исхода
//
//    // Генерация случайной матрицы смежности
//    generate_adjacency_matrix(adj_matrix, n);
//
//    // Печать сгенерированной матрицы смежности
//    printf("\nСгенерированная матрица смежности:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", adj_matrix[i][j]);
//        }
//        printf("\n");
//    }
//
//    // Нахождение полустепени исхода
//    find_out_degree(adj_matrix, n, out_degrees);
//
//    // Нахождение вершины с максимальной полустепенью исхода
//    int vertex = find_vertex_with_max_out_degree(out_degrees, n);
//    printf("\nВершина с максимальной полустепенью исхода: %d, полустепень: %d\n", vertex, out_degrees[vertex]);
//
//    // Нахождение рёбер, исходящих из этой вершины
//    find_edges_from_vertex(adj_matrix, n, vertex);
//
//    return 0;
//}