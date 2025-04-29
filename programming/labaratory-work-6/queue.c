#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <windows.h>

// Функция создания очереди
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

// Функция удаления всей очереди
void deleteQueue(Queue* queue) {
    Node* current = queue->first;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}

// Проверка на пустоту
int isEmpty(Queue* queue) {
    return queue->first == NULL;
}

// Добавление элемента в очередь
void addElementQueue(Queue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (queue->last != NULL) {
        queue->last->next = newNode;
    }
    queue->last = newNode;

    if (queue->first == NULL) {
        queue->first = newNode;
    }
}

// Удаление элемента из очереди
int deleteElementQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста\n");
        return -1;
    }

    Node* temp = queue->first;
    int value = temp->data;
    queue->first = queue->first->next;

    if (queue->first == NULL) {
        queue->last = NULL;
    }

    free(temp);
    return value;
}

// Вывод очереди
void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста\n");
        return;
    }

    Node* current = queue->first;
    printf("Очередь: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}