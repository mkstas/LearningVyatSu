#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float p;
    struct Node *left, *right;
} Node;

void print_code(Node* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 0;
        print_code(root->left, codes, top + 1);
    }

    if (root->right) {
        codes[top] = 1;
        print_code(root->right, codes, top + 1);
    }

    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
        }
        printf(" ");
    }
}

int compare(const void* left, const void* right) {
    Node* left_node = *(Node**)left;
    Node* right_node = *(Node**)right;
    return left_node->p > right_node->p;
}

int main() {
    int n;
    scanf("%d", &n);

    struct Node* nodes[n];

    for (int i = n - 1; i >= 0; i--) {
        Node* node = (Node*)malloc(sizeof(Node));
        scanf("%f", &node->p);
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }

    qsort(nodes, n, sizeof(Node*), compare);

    do {
        qsort(nodes, n, sizeof(Node*), compare);

        Node* left = nodes[0];
        Node* right = nodes[1];
        Node* node = (Node*)malloc(sizeof(Node));
        node->p = left->p + right->p;
        node->left = left;
        node->right = right;
        nodes[0] = node;

        for (int i = 1; i < n - 1; i++) {
            nodes[i] = nodes[i + 1];
        }
        n--;
    } while (n > 1);

    int codes[32];
    print_code(nodes[0], codes, 0);

    return 0;
}