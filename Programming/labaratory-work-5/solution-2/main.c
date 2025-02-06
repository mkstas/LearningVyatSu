#include <stdio.h>

#define size 100

static sort(int array[], int n, void(*comparator)(int array[], int n)) {
	int max = array[0];

	for (int i = 1; i < n; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}

	for (int exp = 1; max / exp > 0; exp *= 10) {
		int sorted[size] = { 0 };
		int count[10] = { 0 };

		for (int i = 0; i < n; i++) {
			count[(array[i] / exp) % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		for (int i = n - 1; i >= 0; i--) {
			sorted[count[(array[i] / exp) % 10] - 1] = array[i];
			count[(array[i] / exp) % 10]--;
		}

		for (int i = 0; i < n; i++) {
			printf("%d ", sorted[i]);
			array[i] = sorted[i];
		}
		printf("\n");
	}
}

static void comparator_min(int array[], int n) {

}

static void comparator_max(int array[], int n) {
	
}

int main() {
	FILE* input = fopen("../input.txt", "r");
	FILE* output = fopen("../output.txt", "w");

	int array[size] = { 0 };
	int n = 0;

	while (fscanf_s(input, "%d", &array[n]) != EOF) n++;

	fclose(input);

	void(*comparator)(int array[], int n);

	comparator = comparator_min;
	//comparator = comparator_max;

	sort(array, n, comparator);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", array[i]);
	}

	fclose(output);

	return 0;
}