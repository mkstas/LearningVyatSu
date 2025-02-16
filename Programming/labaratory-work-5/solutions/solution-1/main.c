#include <stdio.h>

#define size 100
#define range 1000

void sort(int array[], int n, void(*comparator)(int array[], int count[])) {
	int count[range] = { 0 };

	for (int i = 0; i < n; i++) {
		count[array[i]]++;
	}

	comparator(array, count);
}

void comparator_min(int array[], int count[]) {
	int k = 0;

	for (int i = 0; i < range; i++) {
		for (int j = 0; j < count[i]; j++) {
			array[k] = i;
			k++;
		}
	}
}

void comparator_max(int array[], int count[]) {
	int k = 0;

	for (int i = range - 1; i >= 0; i--) {
		for (int j = 0; j < count[i]; j++) {
			array[k] = i;
			k++;
		}
	}
}

int main() {
	FILE* input = fopen("../input.txt", "r");
	FILE* output = fopen("../output.txt", "w");

	int array[size] = { 0 };
	int n = 0;

	while (fscanf_s(input, "%d", &array[n]) != EOF) n++;

	fclose(input);

	void(*comparator)(int array[], int count[]);

	comparator = comparator_min;
	//comparator = comparator_max;

	sort(array, n, comparator);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}

	fclose(output);

	return 0;
}