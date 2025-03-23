//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define MAX_N 10
//#define MIN_N 4
//
//// ������� ��� ��������� ��������� ������� ��������� ��� �������
//void generate_adjacency_matrix(int adj_matrix[MAX_N][MAX_N], int n) {
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            adj_matrix[i][j] = rand() % 2; // ��������� �������� 0 ��� 1
//        }
//    }
//}
//
//// ������� ��� ���������� ����������� ������ ������ �������
//void find_out_degree(int adj_matrix[MAX_N][MAX_N], int n, int out_degrees[MAX_N]) {
//    for (int i = 0; i < n; i++) {
//        out_degrees[i] = 0;
//        for (int j = 0; j < n; j++) {
//            out_degrees[i] += adj_matrix[i][j]; // ��������� �������� � ������ ��� ������� i
//        }
//    }
//}
//
//// ������� ��� ������ ������� � ������������ ������������ ������
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
//// ������� ��� ������ ����, ��������� �� �������
//void find_edges_from_vertex(int adj_matrix[MAX_N][MAX_N], int n, int vertex) {
//    printf("и���, ��������� �� ������� %d: ", vertex);
//    for (int i = 0; i < n; i++) {
//        if (adj_matrix[vertex][i] == 1) {
//            printf("(%d -> %d) ", vertex, i);
//        }
//    }
//    printf("\n");
//}
//
//int main() {
//    srand(time(NULL)); // ������������� ���������� ��������� �����
//
//    int n;
//    printf("������� ����������� ������� (4 <= n <= 10): ");
//    scanf("%d", &n);
//
//    // �������� �� ���������� ��������
//    while (n < MIN_N || n > MAX_N) {
//        printf("����������� ������ ���� �� 4 �� 10. ������� �����: ");
//        scanf("%d", &n);
//    }
//
//    int adj_matrix[MAX_N][MAX_N];  // ������� ���������
//    int out_degrees[MAX_N];         // ������ ��� �������� ����������� ������
//
//    // ��������� ��������� ������� ���������
//    generate_adjacency_matrix(adj_matrix, n);
//
//    // ������ ��������������� ������� ���������
//    printf("\n��������������� ������� ���������:\n");
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", adj_matrix[i][j]);
//        }
//        printf("\n");
//    }
//
//    // ���������� ����������� ������
//    find_out_degree(adj_matrix, n, out_degrees);
//
//    // ���������� ������� � ������������ ������������ ������
//    int vertex = find_vertex_with_max_out_degree(out_degrees, n);
//    printf("\n������� � ������������ ������������ ������: %d, �����������: %d\n", vertex, out_degrees[vertex]);
//
//    // ���������� ����, ��������� �� ���� �������
//    find_edges_from_vertex(adj_matrix, n, vertex);
//
//    return 0;
//}