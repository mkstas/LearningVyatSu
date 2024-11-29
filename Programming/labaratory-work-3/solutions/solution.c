#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void print_menu() {
    system("cls");
    printf("1. Ввод верхнего предела\n");
    printf("2. Ввод нижнего предела\n");
    printf("3. Ввод шага интегрирования\n");
    printf("4. Расчет интеграла\n");
    printf("5. Расчет погрешности\n");
    printf("> ");
}

int main() {
    setlocale(LC_ALL, "");

    print_menu();

    int point;

    scanf("%d", &point);

    switch (point)
    {
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        default:
            print_menu();
            break;
    }

    return 0;
}