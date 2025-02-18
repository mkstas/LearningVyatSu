#include <stdio.h>
#include <stdlib.h>

void sort(int n, int array[], void(*comparator)(int range, int min, int array[], int count[]))
{
	int min = array[0];
	int max = array[0];

	for (int i = 1; i < n; i++) {
		if (array[i] < min) min = array[i];
		if (array[i] > max) max = array[i];
	}

	int range = max - min + 1;
	int* count = (int*)calloc(range, sizeof(int));

	for (int i = 0; i < n; i++) count[array[i] - min]++;

	comparator(range, min, array, count);
}

void comparatorUp(int range, int min, int array[], int count[])
{
	int index = 0;
	for (int i = 0; i < range; i++) {
		while (count[i] > 0) {
			count[i]--;
			array[index] = i + min;
			index++;
		}
	}
}

void comparatorDown(int range, int min, int array[], int count[])
{
	int index = 0;
	for (int i = range - 1; i >= 0; i--) {
		while (count[i] > 0) {
			count[i]--;
			array[index] = i + min;
			index++;
		}
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

	void(*comparator)(int range, int min, int array[], int count[]);
	comparator = comparatorUp;
	sort(n, array, comparator);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}
	fclose(output);

	return 0;
}