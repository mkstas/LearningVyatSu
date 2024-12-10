#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float curve(float x)
{
    return 2 * pow(x, 3) - 2 * pow(x, 2) + 0 * x + 16;
}

float antiderivative(float x)
{
    return 0.5 * pow(x, 4) - 2.0 / 3.0 * pow(x, 3) + 16 * x;
}

float find_x() {
    float left = -2;
    float right = -1.5;
    float center;

    while (right + left > 1e-10) {
        center = (left + right) / 2;

        if (curve(center) * curve(right) < 0) {
            left = center;
        } else {
            right = center;
        }
    }

    float x = (left + right) / 2;

    return x;
}

float left_rect(float a, float b, int n)
{
    float h = (b - a) / n;
    float s = 0.0;

    for (int i = 0; i < n; i++)
    {
        float y = curve(a + i * h);
        if (y > 0)
            s += y * h;
    }

    return abs(s);
}

float calc_error(float a, float b, int n, float *abs_error, float *rel_error)
{
    float res = left_rect(a, b, n);
    float exact = fabs(antiderivative(b) - antiderivative(a));

    *abs_error = fabs(res - exact);

    if (exact != 0) {
        *rel_error = *abs_error / exact * 100;
    }

    return exact;
}

void print_menu()
{
    printf("\033[0d\033[2J");
    printf("1. Ввод верхнего предела\n");
    printf("2. Ввод нижнего предела\n");
    printf("3. Ввод шага интегрирования\n");
    printf("4. Рассчет интеграла\n");
    printf("5. Рассчет погрешности\n");
    printf("6. Выход\n");
}

int main()
{
    int choice, n = 0, exit = 1;
    float a, b;

    print_menu();
    printf(">  ");

    scanf("%d", &choice);

    while (exit)
    {
        switch (choice)
        {
        case 1:
            printf("Верхний предел: ");
            scanf("%f", &a);
            if (a < find_x()) a = find_x();
            print_menu();
            printf(">  ");
            scanf("%d", &choice);
            break;

        case 2:
            printf("Нижний предел: ");
            scanf("%f", &b);
            print_menu();
            printf(">  ");
            scanf("%d", &choice);
            break;

        case 3:
            printf("Шаг интегрирования: ");
            scanf("%d", &n);
            print_menu();
            printf(">  ");
            scanf("%d", &choice);
            break;

        case 4:
            print_menu();
            if (a && b && n != 0) {
                printf("Площадь: %f\n", left_rect(a, b, n));
            } else {
                printf("Не введены пределы и шаг интегрирования\n");
            }
            printf(">  ");
            scanf("%d", &choice);
            break;

        case 5:
            print_menu();
            if (a && b && n != 0) {
                float abs_error, rel_error = 0.0;
                float exact = calc_error(a, b, n, &abs_error, &rel_error);
                printf("Метод левых прямоугольников: %f\n", left_rect(a, b, n));
                printf("Метод Ньютона-Лейбница: %f\n", exact);
                printf("Абсолютная погрешность: %f\n", abs_error);
                printf("Относительная погрешность: %f%%\n", rel_error);
            } else {
                printf("Не введены пределы и шаг интегрирования\n");
            }
            printf(">  ");
            scanf("%d", &choice);
            break;

        case 6:
            exit = 0;
            printf("\033[0d\033[2J");
            break;

        default:
            print_menu();
            printf(">  ");
            break;
        }
    }

    return 0;
}