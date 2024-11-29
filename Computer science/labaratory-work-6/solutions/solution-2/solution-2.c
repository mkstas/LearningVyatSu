#include <stdio.h>

struct Node {
    char symb;
    float p;
    struct Node *left, *right;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Node nodes[n];

    for (int i = 0; i < n; i++) {
        scanf("%f", &nodes[i].p);
    }

    return 0;
}