#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float p;
    struct Node* left, * right;
} Node;

void printCode(Node* root, int codes[], int top)
{
    if (root->left) {
        codes[top] = 0;

        printCode(root->left, codes, top + 1);
    }

    if (root->right) {
        codes[top] = 1;

        printCode(root->right, codes, top + 1);
    }

    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
        }

        printf(" ");
    }
}

int main()
{
    int n;

    scanf_s("%d", &n);

    struct Node** nodes = (Node*)malloc(sizeof(Node) * n);

    for (int i = 0; i < n; i++) {
        Node* node = (Node*)malloc(sizeof(Node));

        scanf_s("%f", &node->p);

        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }

    while (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (nodes[j]->p > nodes[j + 1]->p) {
                    Node* node = nodes[j];
                    nodes[j] = nodes[j + 1];
                    nodes[j + 1] = node;
                }
            }
        }

        Node* left = nodes[1];
        Node* right = nodes[0];
        Node* node = (Node*)malloc(sizeof(Node));

        node->p = left->p + right->p;
        node->left = left;
        node->right = right;
        nodes[0] = node;

        for (int i = 1; i < n - 1; i++) {
            nodes[i] = nodes[i + 1];
        }

        n--;
    }

    int codes[32];

    printCode(nodes[0], codes, 0);

    return 0;
}