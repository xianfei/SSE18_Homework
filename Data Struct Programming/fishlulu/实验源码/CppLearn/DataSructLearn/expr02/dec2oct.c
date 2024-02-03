//
// Created by 86130 on 2023/10/16.
//
#include <stdio.h>
#define MAX_SIZE 100

//定义顺栈结构
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
    printf("栈已经满了,无法压入\n");
  }
}

int pop(Stack* stack) {
  if (!isStackEmpty(stack)) {
    return stack->data[stack->top--];
  } else {
    printf("栈已经空了,无法弹出元素\n");
    return -1;
  }
}

void decimalToOctal(int decimal) {
  Stack stack;
  initStack(&stack);

  if (decimal == 0) {
    printf("八进制数为0\n");
    return;
  }

  while (decimal > 0) {
    push(&stack, decimal % 8);
    decimal /= 8;
  }

  printf("八进制数为: ");
  while (!isStackEmpty(&stack)) {
    int digit = pop(&stack);
    printf("%d", digit);
  }
  printf("\n");
}

int main() {
  int decimal;
  printf("请输入一个非负十进制数: ");
  scanf("%d", &decimal);

  if (decimal < 0) {
    printf("输入的不是非负数\n");
  } else {
    decimalToOctal(decimal);
  }
  printf("程序结束\n");
  return 0;
}
