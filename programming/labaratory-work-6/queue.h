#ifndef QUEUE_H
#define QUEUE_H

// Узел очереди
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Очередь
typedef struct Queue {
    Node* first; // Указатель на первый элемент
    Node* last;  // Указатель на последний элемент
} Queue;

Queue* createQueue();       // Создание очереди
void deleteQueue(Queue* queue); // Удаление очереди
int isEmpty(Queue* queue);      // Проверка на пустоту
void addElementQueue(Queue* queue, int value); // Добавление элемента
int deleteElementQueue(Queue* queue); // Удаление элемента
void printQueue(Queue* queue); // Печать очереди

#endif
