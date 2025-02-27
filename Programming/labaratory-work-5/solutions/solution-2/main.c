#include <stdio.h>
#include <stdlib.h>

void radixSort(int n, int array[])
{
	int max = array[0];

	for (int i = 1; i < n; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}

	for (int exp = 1; max / exp > 0; exp *= 10) {
		int* temp = (int*)calloc(n, sizeof(int));
		int count[10] = { 0 };

		for (int i = 0; i < n; i++) {
			count[array[i] / exp % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		for (int i = n - 1; i >= 0; i--) {
			temp[count[array[i] / exp % 10] - 1] = array[i];
			count[array[i] / exp % 10]--;
		}

		for (int i = 0; i < n; i++) {
			array[i] = temp[i];
		}
	}
}

void sort(int n, int array[], void(*comparator)(int array[], int negative[], int negCount, int positive[], int posCount))
{
	int* negative = (int*)calloc(n, sizeof(int));
	int* positive = (int*)calloc(n, sizeof(int));
	int negCount = 0, posCount = 0;

	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			negative[negCount++] = -array[i];
		}
		else {
			positive[posCount++] = array[i];
		}
	}

	radixSort(negCount, negative);
	radixSort(posCount, positive);

	for (int i = 0; i < negCount; i++) {
		negative[i] = -negative[i];
	}

	comparator(array, negative, negCount, positive, posCount);
}

void comparatorUp(int array[], int negative[], int negCount, int positive[], int posCount)
{
	int j = 0;

	for (int i = negCount - 1; i >= 0; i--) {
		array[j++] = negative[i];
	}

	for (int i = 0; i < posCount; i++) {
		array[j++] = positive[i];
	}
}

void comparatorDown(int array[], int negative[], int negCount, int positive[], int posCount)
{
	int j = 0;

	for (int i = posCount - 1; i >= 0; i--) {
		array[j++] = positive[i];
	}

	for (int i = 0; i < negCount; i++) {
		array[j++] = negative[i];
	}
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

	void(*comparator)(int array[], int negative[], int negCount, int positive[], int posCount);
	comparator = comparatorUp;
	sort(n, array, comparator);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}
	fclose(output);

	return 0;
}