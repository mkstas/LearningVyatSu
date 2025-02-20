#include <stdio.h>
#include <stdlib.h>

void sort(int n, int array[])
{
	int* temp = (int*)calloc(n, sizeof(int));

	for (int bit = 0; bit < 32; bit++) {
		int count[2] = { 0, 0 };

		for (int i = 0; i < n; i++) {
			count[(array[i] >> bit) & 1]++;
		}

		count[1] += count[0];

		for (int i = n - 1; i >= 0; i--) {
			temp[--count[(array[i] >> bit) & 1]] = array[i];
		}

		for (int i = 0; i < n; i++) {
			array[i] = temp[i];
		}
	}
}

void comparatorUp()
{

}

void comoaratorDown()
{

}

int main()
{
	FILE* input = fopen("../input.txt", "r");
	FILE* output = fopen("../output.txt", "w");

	int n = 0;
	fscanf_s(input, "%d", &n);
	int* array = (int*)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		fscanf_s(input, "%d", &array[i]);
	}
	fclose(input);

	void(*comparator)();
	comparator = comparatorUp;
	sort(n, array);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}
	fclose(output);

	return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAX_BITS 32  // ���������� ��� ��� ������������� ����� � 32-������ �������
//
//// ������� ��� ��������� i-�� ���� ����� num
//int get_bit(int num, int i) {
//    return (num >> i) & 1;
//}
//
//// ������� ��� ���������� �� �������� �������
//void radix_sort(int arr[], int n) {
//    int* output = (int*)malloc(n * sizeof(int));  // ��������� ������ ��� ��������������� ��������
//
//    // ��� ������� ���� ������� � �������� (�� 0 �� 31)
//    for (int bit = 0; bit < MAX_BITS; bit++) {
//        int count[2] = { 0, 0 };  // �������� ��� ���� ��������� �������� ���� (0 ��� 1)
//
//        // ������������ ���������� 0 � 1 �� ������� ����
//        for (int i = 0; i < n; i++) {
//            int bit_val = get_bit(arr[i], bit);
//            count[bit_val]++;
//        }
//
//        // ����������� ������� ��� ������������� �� ��������� �������
//        count[1] += count[0];
//
//        // ��������� �������� ������ � ������ �������� ����
//        for (int i = n - 1; i >= 0; i--) {
//            int bit_val = get_bit(arr[i], bit);
//            output[--count[bit_val]] = arr[i];
//        }
//
//        // �������� ��������������� �������� ������� � ������������ ������
//        for (int i = 0; i < n; i++) {
//            arr[i] = output[i];
//        }
//    }
//
//    free(output);  // ����������� ������
//}
//
//// ������� ��� ������ �������
//void print_array(int arr[], int n) {
//    for (int i = 0; i < n; i++) {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//}
//
//// ������� ��� ���������� � ������ ����� (������� �������������, ����� �������������)
//void sort_with_signs(int arr[], int n) {
//    // �������� ������ �� ������������� � ������������� �����
//    int* negatives = (int*)malloc(n * sizeof(int));
//    int* positives = (int*)malloc(n * sizeof(int));
//    int neg_count = 0, pos_count = 0;
//
//    for (int i = 0; i < n; i++) {
//        if (arr[i] < 0) {
//            negatives[neg_count++] = arr[i];
//        }
//        else {
//            positives[pos_count++] = arr[i];
//        }
//    }
//
//    // ��������� ������������� �����
//    radix_sort(negatives, neg_count);
//
//    // ��������� ������������� �����
//    radix_sort(positives, pos_count);
//
//    // ���������� ��������������� ������� (������������� �������)
//    int i = 0;
//    for (i = 0; i < neg_count; i++) {
//        arr[i] = negatives[i];
//    }
//    for (int j = 0; j < pos_count; j++) {
//        arr[i + j] = positives[j];
//    }
//
//    free(negatives);
//    free(positives);
//}
//
//int main() {
//    // ������ ������� � �������������� �������
//    int arr[] = { 3, -5, 2, -8, 6, -1 };
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    printf("�������� ������:\n");
//    print_array(arr, n);
//
//    sort_with_signs(arr, n);
//
//    printf("��������������� ������:\n");
//    print_array(arr, n);
//
//    return 0;
//}