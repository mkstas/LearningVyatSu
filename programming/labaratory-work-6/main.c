#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

void readNumber(int* value) {
    printf("������� ��������: ");
    scanf_s("%d", value);
}

// ������� ��� ��������� ������ ������� (������� ������� � ����� ������)
void getCleanCommand(const char* input, char* cleanCommand) {
    const char* start = input;
    while (*start && isspace(*start)) start++; // ���������� ��������� �������

    if (*start == '\0') {
        cleanCommand[0] = '\0';
        return;
    }

    const char* end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) end--; // ���������� �������� �������

    strncpy_s(cleanCommand, 20, start, end - start + 1);
    cleanCommand[end - start + 1] = '\0';
}

void autocompleteCommand(char* input, size_t size) {
    char* commands[] = { "add", "delete", "print", "check", "exit" };
    int numCommands = 5;
    char cleanInput[20] = { 0 };
    getCleanCommand(input, cleanInput);

    if (strlen(cleanInput) == 0) return;

    for (int i = 0; i < numCommands; i++) {
        if (strncmp(commands[i], cleanInput, strlen(cleanInput)) == 0) {
            strcpy_s(input, size, commands[i]);
            printf("\r������� �������: %s", input);
            break;
        }
    }
}

void clearCurrentLine(size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("\b \b");
    }
}

void handleBackspace(char* command, size_t* idx) {
    if (*idx > 0) {
        (*idx)--;
        command[*idx] = '\0';
        printf("\b \b");
    }
}

void handleTab(char* command, size_t* idx) {
    clearCurrentLine(*idx);
    autocompleteCommand(command, 20);
    *idx = strlen(command);
}

void handleArrowUp(char* command, size_t* idx, char history[][20], int historyCount, int* historyPos) {
    if (historyCount > 0 && *historyPos < historyCount - 1) {
        (*historyPos)++;
        clearCurrentLine(*idx);
        strcpy_s(command, 20, history[historyCount - 1 - *historyPos]);
        printf("%s", command);
        *idx = strlen(command);
    }
}

void handleArrowDown(char* command, size_t* idx, char history[][20], int historyCount, int* historyPos) {
    if (*historyPos > 0) {
        (*historyPos)--;
        clearCurrentLine(*idx);
        strcpy_s(command, 20, history[historyCount - 1 - *historyPos]);
        printf("%s", command);
        *idx = strlen(command);
    }
}

void handleEnter(char* command, size_t idx, char history[][20], int* historyCount, int* historyPos) {
    char cleanCommand[20] = { 0 };
    getCleanCommand(command, cleanCommand);

    if (strlen(cleanCommand) > 0) {
        if (*historyCount < 10) {
            strcpy_s(history[*historyCount], 20, cleanCommand);
            (*historyCount)++;
        }
        else {
            for (int i = 0; i < 9; i++) {
                strcpy_s(history[i], 20, history[i + 1]);
            }
            strcpy_s(history[9], 20, cleanCommand);
        }
    }
    *historyPos = -1;
}

void handleRegularChar(char* command, size_t* idx, int ch) {
    if (*idx < 19 && isprint(ch)) {
        command[*idx] = (char)ch;
        (*idx)++;
        putchar(ch);
    }
}

void processCommand(Queue* queue, const char* command) {
    char cleanCommand[20] = { 0 };
    getCleanCommand(command, cleanCommand);

    if (strlen(cleanCommand) == 0) {
        printf("\n�������� �������. ���������� �����.\n");
        return;
    }

    int value;
    if (strcmp(cleanCommand, "add") == 0) {
        readNumber(&value);
        addElementQueue(queue, value);
        printf("\n������� %d �������� � �������\n", value);
    }
    else if (strcmp(cleanCommand, "delete") == 0) {
        if (isEmpty(queue)) {
            printf("\n������� �����, �������� ����������.\n");
        }
        else {
            value = deleteElementQueue(queue);
            if (value != -1) {
                printf("\n������� %d ������ �� �������\n", value);
            }
        }
    }
    else if (strcmp(cleanCommand, "print") == 0) {
        if (isEmpty(queue)) {
            printf("\n������� �����.\n");
        }
        else {
            printQueue(queue);
            printf("\n");
        }
    }
    else if (strcmp(cleanCommand, "check") == 0) {
        if (isEmpty(queue)) {
            printf("\n������� �����.\n");
        }
        else {
            printf("\n������� �� �����.\n");
        }
    }
    else if (strcmp(cleanCommand, "exit") == 0) {
        deleteQueue(queue);
        printf("\n�����\n");
        exit(0);
    }
    else {
        printf("\n�������� �������. ���������� �����.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    Queue* queue = createQueue();
    char command[20] = { 0 };
    size_t idx = 0;
    char history[10][20] = { 0 };
    int historyCount = 0;
    int historyPos = -1;

    while (1) {
        printf("\n����:\n");
        printf("add - �������� �������\n");
        printf("delete - ������� �������\n");
        printf("print - ������ �������\n");
        printf("check - �������� �� ������� �������\n");
        printf("exit - �����\n");
        printf("������� �������: ");

        memset(command, 0, sizeof(command));
        idx = 0;

        while (1) {
            int ch = _getch();

            if (ch == 13) { // Enter
                handleEnter(command, idx, history, &historyCount, &historyPos);
                break;
            }
            else if (ch == 8) { // Backspace
                handleBackspace(command, &idx);
            }
            else if (ch == 9) { // Tab
                handleTab(command, &idx);
            }
            else if (ch == 0xE0 || ch == 0) { // ����������� ������� (�������)
                ch = _getch();
                if (ch == 72) { // ������� �����
                    handleArrowUp(command, &idx, history, historyCount, &historyPos);
                }
                else if (ch == 80) { // ������� ����
                    handleArrowDown(command, &idx, history, historyCount, &historyPos);
                }
            }
            else {
                handleRegularChar(command, &idx, ch);
            }
        }

        processCommand(queue, command);
    }

    return 0;
}