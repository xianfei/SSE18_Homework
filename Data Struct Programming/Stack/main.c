#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR -1
#define Status int
typedef int ElemType;

#define DEFAULT_CAPACITY 100

typedef struct {
    ElemType *array;
    int size, capacity;
} Stack;

Status initStack(Stack *s) {
    if (!(s->array = malloc(DEFAULT_CAPACITY * sizeof(Stack))))return ERROR;
    s->size = 0;
    s->capacity = DEFAULT_CAPACITY;
    return OK;
}

Status push(Stack *s, int data) {
    if (s->size >= s->capacity)if (!(s->array = realloc(s->array, s->capacity * 2 * sizeof(Stack))))return ERROR;
    s->array[s->size++] = data;
    return OK;
}

Status pop(Stack *s, int *data) {
    if (!s->size)return ERROR;
    *data = s->array[--s->size];
    return OK;
}

int main() {
    Stack stack;
    // 初始化stack
    initStack(&stack);
    // push 0-199 to stack
    for (int i = 0; i < 200; i++)push(&stack, i);
    int num;
    // pop them
    for (int i = 0; i < 200; i++) {
        pop(&stack, &num);
        printf("%d ", num);
    }
}