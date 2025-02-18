#include <stdio.h>

#define size 100

static void sort(int array[], int n, void(*comparator)(int count[]))
{
	int max = array[0];

	for (int i = 1; i < n; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}

	for (int exp = 1; max / exp > 0; exp *= 10) {
		int count[10] = { 0 };
		int temp[size] = { 0 }; 

		for (int i = 0; i < n; i++) {
			count[array[i] / exp % 10]++;
		}

		comparator(count);

		for (int i = n - 1; i >= 0; i--) {
			temp[count[array[i] / exp % 10] - 1] = array[i];
			count[array[i] / exp % 10]--;
		}

		for (int i = 0; i < n; i++) {
			array[i] = temp[i];
		}
	}
}

static void comparatorUp(int count[])
{
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
}

static void comparatorDown(int count[])
{
	for (int i = 8; i >= 0; i--) {
		count[i] += count[i + 1];
	}
}

int main()
{
	FILE* input = fopen("../input.txt", "r");
	FILE* output = fopen("../output.txt", "w");

	int array[size] = { 0 };
	int n = 0;

	fscanf_s(input, "%d", &n);

	for (int i = 0; i < n; i++) fscanf_s(input, "%d", &array[i]);

	fclose(input);

	void(*comparator)(int count[]);

	comparator = comparatorUp;

	sort(array, n, comparator);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}

	fclose(output);

	return 0;
}