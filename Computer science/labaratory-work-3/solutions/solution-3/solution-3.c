#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int quantity(int K, int M, char *fract_str) {
    return ceil(strlen(fract_str) * (log(K) / log(M)));
}

void divide_num(char *X, char *integ_str, char *fract_str) {
    sprintf(integ_str, "%s", strtok(X, "."));
    sprintf(fract_str, "%s", strtok(NULL, "."));
}

void translate_to_10(int K, int M, char *X, char *integ_str, char *fract_str) {
    int integ_sum = 0;
    float fract_sum = 0;

    for (int i = 0; i < strlen(integ_str); i++) {
        integ_sum += (integ_str[i] - '0') * pow(K, strlen(integ_str) - i - 1);
    }

    for (int i = 0; i < quantity(K, M, fract_str); i++) {
        fract_sum += (fract_str[i] - '0') * (1 / pow(K, i + 1));
    }

    sprintf(X, "%g", integ_sum + fract_sum);
}

void translate_to_M(int K, int M, char *X, char *integ_str, char *fract_str) {
    char integ_M[32], fract_M[32] = "", bf[32] = "0.";
    itoa(atoi(integ_str), integ_M, M);
    strcat(bf, fract_str);
    float fract = atof(bf);

    for (int i = 0; i < quantity(K, M, fract_str); i++) {
        fract *= M;
        if (fract >= 0) {
            char bf[2];
            itoa((int)floor(fract), bf, 10);
            strcat(fract_M, bf);
            fract -= floor(fract);
        } else {
            strcat(fract_M, "0");
        }
    }

    sprintf(X, "%s", integ_M);
    strcat(X, ".");
    strcat(X, fract_M);
}

int main() {
    char X[32]; int K, M; 
    char integ_str[16], fract_str[16];
    scanf("%s %d %d", X, &K, &M);

    if (K < 2 || K > 10 || M < 2 || M > 10) {
        printf("Неверный диапазон оснований систем счисления");
        return 0;
    }

    char *ptr = strchr(X, K + '0');

    if (ptr != NULL) {
        printf("Число не соответсвует числу основанию");
        return 0;
    }

    if (K < 10) {
        divide_num(X, integ_str, fract_str);
        translate_to_10(K, M, X, integ_str, fract_str);
    }

    divide_num(X, integ_str, fract_str);
    translate_to_M(K, M, X, integ_str, fract_str);

    printf("%s", X);

    return 0;
}