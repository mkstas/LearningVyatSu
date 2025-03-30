#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

static double quantity(int k, int m, char* fractStr)
{
    return ceil(strlen(fractStr) * (log(k) / log(m)));
}

static void divideNumber(char* x, char* integStr, char* fractStr)
{
    sprintf(integStr, "%s", strtok(x, "."));
    sprintf(fractStr, "%s", strtok(NULL, "."));
}

static void translateTo10(int k, int m, char* x, char* integStr, char* fractStr)
{
    double integSum = 0;
    double fractSum = 0.0;

    for (int i = 0; i < strlen(integStr); i++)
        integSum += (integStr[i] - '0') * pow(k, strlen(integStr) - i - 1);

    for (int i = 0; i < quantity(k, m, fractStr); i++)
        fractSum += (fractStr[i] - '0') * (1 / pow(k, i + 1));

    sprintf(x, "%g", integSum + fractSum);
}

static void translateToM(int k, int m, char* x, char* integStr, char* fractStr)
{
    char integM[32], fractM[32] = "", buffer[32] = "0.";

    _itoa(atoi(integStr), integM, m);
    strcat(buffer, fractStr);

    double fract = atof(buffer);

    for (int i = 0; i < quantity(k, m, fractStr); i++) {
        fract *= m;

        if (fract >= 0) {
            char buffer[2];
            _itoa((int)floor(fract), buffer, 10);
            strcat(fractM, buffer);
            fract -= floor(fract);
        } else {
            strcat(fractM, "0");
        }
    }

    sprintf(x, "%s", integM);
    strcat(x, ".");
    strcat(x, fractM);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    int k, m;
    char x[32];
    char integStr[16] = { ' ' };
    char fractStr[16] = { ' ' };

    scanf("%s %d %d", x, &k, &m);

    if (k < 2 || k > 10 || m < 2 || m > 10) {
        printf("Неверный диапазон оснований систем счисления");

        return 0;
    }

    char* ptr = strchr(x, k + '0');

    if (ptr != NULL) {
        printf("Число не соответсвует числу основанию");

        return 0;
    }

    if (k < 10) {
        divideNumber(x, integStr, fractStr);
        translateTo10(k, m, x, integStr, fractStr);
    }

    divideNumber(x, integStr, fractStr);
    translateToM(k, m, x, integStr, fractStr);

    printf("%s", x);

    return 0;
}