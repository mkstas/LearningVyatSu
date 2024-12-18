#include <stdio.h>
#include <stdlib.h>

typedef struct Elem {
    int info, prev, next;
} Elem;

int main()
{
    int n;
    scanf("%d", &n);

    struct Elem* list = (Elem*)malloc(sizeof(Elem) * 2 * n);

    list[0].prev = 0;
    list[0].next = 1;
    list[n - 1].next = 0;
    list[n - 1].prev = n - 1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i].info);

        if (i != 0 && i != n - 1) {
            list[i].prev = i;
            list[i].next = i + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", list[i].prev, list[i].info, list[i].next);
    }

    return 0;
}
