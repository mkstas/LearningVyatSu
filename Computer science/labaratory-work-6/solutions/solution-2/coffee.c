#include <stdlib.h>

typedef struct Node {
    char symbol;
    float prob;
    struct Node *left, *right;
} Node;

// Функция для создания нового узла
Node* newNode(char symbol, float prob) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->prob = prob;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для сравнения узлов по вероятности
int compareNodes(const void* a, const void* b) {
    Node* aNode = *(Node**)a;
    Node* bNode = *(Node**)b;
    return aNode->prob > bNode->prob;
}

// Функция для построения дерева Хаффмана
Node* buildHuffmanTree(Node* nodes[], int n) {
    while (n > 1) {
        // Сортировка узлов по вероятности
        qsort(nodes, n, sizeof(Node*), compareNodes);

        // Выбираем два узла с минимальной вероятностью
        Node* left = nodes[0];
        Node* right = nodes[1];

        // Создаем новый узел, который объединяет два выбранных
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->symbol = '\0';  // Это будет внутренний узел
        newNode->prob = left->prob + right->prob;
        newNode->left = left;
        newNode->right = right;

        // Сдвигаем оставшиеся узлы в массиве, добавляем новый узел
        nodes[0] = newNode;
        for (int i = 1; i < n - 1; i++) {
            nodes[i] = nodes[i + 1];
        }

        n--; // Уменьшаем количество узлов
    }

    return nodes[0]; // Возвращаем корень дерева
}

// Функция для обхода дерева и получения кодов
void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // Если это листовой узел, выводим символ и код
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->symbol);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter number of symbols: ");
    scanf("%d", &n);

    Node* nodes[n];
    for (int i = 0; i < n; i++) {
        char symbol;
        float prob;
        printf("Enter symbol and probability for node %d: ", i + 1);
        scanf(" %c %f", &symbol, &prob);
        nodes[i] = newNode(symbol, prob);
    }

    // Сортировка узлов по вероятности
    qsort(nodes, n, sizeof(Node*), compareNodes);

    // Построение дерева Хаффмана
    Node* root = buildHuffmanTree(nodes, n);

    // Получение кодов
    int arr[100];
    int top = 0;
    printCodes(root, arr, top);

    return 0;
}
