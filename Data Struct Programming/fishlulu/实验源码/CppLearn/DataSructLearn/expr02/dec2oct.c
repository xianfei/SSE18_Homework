//
// Created by 86130 on 2023/10/16.
//
#include <stdio.h>
#define MAX_SIZE 100

//����˳ջ�ṹ
typedef int elem_type;
typedef struct {
  int data[MAX_SIZE];
  int top;
} Stack;

void initStack(Stack* stack) {
  stack->top = -1;
}

int isStackEmpty(Stack* stack) {
  return stack->top == -1;
}

int isStackFull(Stack* stack) {
  return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int value) {
  if (!isStackFull(stack)) {
    stack->data[++stack->top] = value;
  } else {
    printf("ջ�Ѿ�����,�޷�ѹ��\n");
  }
}

int pop(Stack* stack) {
  if (!isStackEmpty(stack)) {
    return stack->data[stack->top--];
  } else {
    printf("ջ�Ѿ�����,�޷�����Ԫ��\n");
    return -1;
  }
}

void decimalToOctal(int decimal) {
  Stack stack;
  initStack(&stack);

  if (decimal == 0) {
    printf("�˽�����Ϊ0\n");
    return;
  }

  while (decimal > 0) {
    push(&stack, decimal % 8);
    decimal /= 8;
  }

  printf("�˽�����Ϊ: ");
  while (!isStackEmpty(&stack)) {
    int digit = pop(&stack);
    printf("%d", digit);
  }
  printf("\n");
}

int main() {
  int decimal;
  printf("������һ���Ǹ�ʮ������: ");
  scanf("%d", &decimal);

  if (decimal < 0) {
    printf("����Ĳ��ǷǸ���\n");
  } else {
    decimalToOctal(decimal);
  }
  printf("�������\n");
  return 0;
}
