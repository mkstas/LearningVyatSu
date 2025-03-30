#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define X -1.71619

static float curve(float x)
{
    return 2 * pow(x, 3) - 2 * pow(x, 2) + 0 * x + 16;
}

static float antiderivative(float x)
{
    return 0.5 * pow(x, 4) - 2.0 / 3.0 * pow(x, 3) + 16 * x;
}

static float newton(float a, float b)
{
    return antiderivative(b) - antiderivative(a);
}

static float leftRect(float a, float b, float h)
{
    float s = 0.0;

    for (float i = a; i < b; i = i + h)
        s += curve(i + h) * h;

    return s;
}

static void printMenu()
{
    system("cls");
    printf("1. Ввод нижнего предела\n");
    printf("2. Ввод верхнего предела\n");
    printf("3. Ввод шага интегрирования\n");
    printf("4. Рассчет интеграла\n");
    printf("5. Рассчет погрешности\n");
}

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    int choice, is_a = 0, is_b = 0, is_h = 0;
    float a, b, h;

    printMenu();
    printf(">  ");
    scanf_s("%d", &choice);

    while (1) {
        switch (choice) {
            case 1:
                printMenu();
                printf("Нижний предел: ");
                scanf_s("%f", &a);

                if (is_b) {
                    while (a >= b) {
                        printf("Введите корректный нижний предел: ");
                        scanf_s("%f", &a);
                    }
                }

                if (a < X) a = X;

                is_a = 1;

                printf(">  ");
                scanf_s("%d", &choice);

                break;

            case 2:
                printMenu();
                printf("Верхний предел: ");
                scanf_s("%f", &b);

                if (is_a) while (a >= b) {
                    printf("Введите корректный верхний предел: ");
                    scanf_s("%f", &b);
                }

                is_b = 1;

                printf(">  ");
                scanf_s("%d", &choice);

                break;

            case 3:
                printMenu();
                printf("Шаг интегрирования: ");
                scanf_s("%f", &h);

                is_h = 1;

                printf(">  ");
                scanf_s("%d", &choice);

                break;

            case 4:
                printMenu();

                if (is_a && is_b && is_h)
                    printf("Площадь: %.2f\n", leftRect(a, b, h));
                else
                    printf("Не введены пределы или шаг интегрирования\n");

                printf(">  ");
                scanf_s("%d", &choice);

                break;

            case 5:
                printMenu();

                if (is_a && is_b && is_h) {
                    printf("Метод левых прямоугольников: %.2f\n", leftRect(a, b, h));
                    printf("Метод Ньютона-Лейбница:      %.2f\n", newton(a, b));
                    printf("Абсолютная погрешность:      %.2f\n", fabs(leftRect(a, b, h) - newton(a, b)));
                    printf("Относительная погрешность:   %.2f%%\n", fabs((leftRect(a, b, h) - newton(a, b)) / newton(a, b) * 100));
                } else {
                    printf("Не введены пределы или шаг интегрирования\n");
                }

                printf(">  ");
                scanf_s("%d", &choice);

                break;

            default:
                printMenu();
                printf(">  ");
                scanf_s("%d", &choice);

                break;
        }
    }

    return 0;
}