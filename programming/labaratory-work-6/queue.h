#ifndef QUEUE_H
#define QUEUE_H

// ���� �������
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// �������
typedef struct Queue {
    Node* first; // ��������� �� ������ �������
    Node* last;  // ��������� �� ��������� �������
} Queue;

Queue* createQueue();       // �������� �������
void deleteQueue(Queue* queue); // �������� �������
int isEmpty(Queue* queue);      // �������� �� �������
void addElementQueue(Queue* queue, int value); // ���������� ��������
int deleteElementQueue(Queue* queue); // �������� ��������
void printQueue(Queue* queue); // ������ �������

#endif
