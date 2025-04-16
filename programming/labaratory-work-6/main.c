#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include "queue.h"

void readNumber(int* value) {
    printf("Введите значение: ");
    scanf_s("%d", value);
}

void autocompleteCommand(char* input, size_t size) {
    char* commands[] = { "add", "delete", "print", "check", "exit" };
    int numCommands = 5;

    for (int i = 0; i < numCommands; i++) {
        if (strncmp(commands[i], input, strlen(input)) == 0) {
            strcpy_s(input, size, commands[i]);
            printf("\rВведите команду: %s", input);
            break;
        }
    }
}

void clearCurrentLine(size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("\b \b");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    Queue* queue = createQueue();
    int value;
    char command[20] = { 0 };
    size_t idx = 0;
    char history[10][20] = { 0 };
    int historyCount = 0;
    int historyPos = -1;

    while (1) {
        printf("\nМеню:\n");
        printf("add - Добавить элемент\n");
        printf("delete - Удалить элемент\n");
        printf("print - Печать очереди\n");
        printf("check - Проверка на пустоту очереди\n");
        printf("exit - Выход\n");
        printf("Введите команду: ");

        memset(command, 0, sizeof(command));
        idx = 0;

        while (1) {
            int ch = _getch(); 

            if (ch == 13) { // Enter
                if (idx > 0) {
                    if (historyCount < 10) {
                        strcpy_s(history[historyCount], sizeof(history[0]), command);
                        historyCount++;
                    }
                    else {
                        for (int i = 0; i < 9; i++) {
                            strcpy_s(history[i], sizeof(history[0]), history[i + 1]);
                        }
                        strcpy_s(history[9], sizeof(history[0]), command);
                    }
                }
                historyPos = -1;
                break;
            }
            else if (ch == 8) { // Backspace
                if (idx > 0) {
                    idx--;
                    command[idx] = '\0';
                    printf("\b \b");
                }
            }
            else if (ch == 9) { // Tab
                clearCurrentLine(idx);
                autocompleteCommand(command, sizeof(command));
                idx = strlen(command);
            }
            else if (ch == 0xE0 || ch == 0) { // Специальные клавиши (стрелки)
                ch = _getch(); // Получаем реальный код клавиши

                if (ch == 72) { // Стрелка вверх
                    if (historyCount > 0 && historyPos < historyCount - 1) {
                        historyPos++;
                        clearCurrentLine(idx);
                        strcpy_s(command, sizeof(command), history[historyCount - 1 - historyPos]);
                        printf("%s", command);
                        idx = strlen(command);
                    }
                }
                else if (ch == 80) { // Стрелка вниз
                    if (historyPos > 0) {
                        historyPos--;
                        clearCurrentLine(idx);
                        strcpy_s(command, sizeof(command), history[historyCount - 1 - historyPos]);
                        printf("%s", command);
                        idx = strlen(command);
                    }
                    else if (historyPos == 0) {
                        historyPos = -1;
                        clearCurrentLine(idx);
                        memset(command, 0, sizeof(command));
                        idx = 0;
                    }
                }
            }
            else if (idx < sizeof(command) - 1 && isprint(ch)) { // Проверка на печатный символ
                command[idx] = (char)ch;
                idx++;
                putchar(ch);
            }
        }


        // Остальной код обработки команд...
        if (strcmp(command, "add") == 0) {
          readNumber(&value);
          addElementQueue(queue, value);
          printf("\nЭлемент %d добавлен в очередь\n", value);
      }
      else if (strcmp(command, "delete") == 0) {
          if (isEmpty(queue)) {
              printf("\nОчередь пуста, удаление невозможно.\n");
          }
          else {
              value = deleteElementQueue(queue);
              if (value != -1) {
                  printf("\nЭлемент %d удален из очереди\n", value);
              }
          }
      }
      else if (strcmp(command, "print") == 0) {
          if (isEmpty(queue)) {
              printf("\nОчередь пуста.\n");
          }
          else {
              printQueue(queue);
              printf("\n");
          }
      }
      else if (strcmp(command, "check") == 0) {
          if (isEmpty(queue)) {
              printf("\nОчередь пуста.\n");
          }
          else {
              printf("\nОчередь не пуста.\n");
          }
      }
      else if (strcmp(command, "exit") == 0) {
          deleteQueue(queue);
          printf("\nВыход\n");
          return 0;
      }
      else {
          printf("\nНеверная команда. Попробуйте снова.\n");
      }
  }

  return 0;
}
