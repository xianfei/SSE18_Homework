#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
  char data[MAX_SIZE];
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

void push(Stack* stack, char value) {
  if (!isStackFull(stack)) {
    stack->data[++stack->top] = value;
  } else {
    printf("Stack is full, cannot push more elements.\n");
  }
}

char pop(Stack* stack) {
  if (!isStackEmpty(stack)) {
    return stack->data[stack->top--];
  } else {
    printf("Stack is empty, cannot pop any elements.\n");
    return '\0';
  }
}

// Check if a right parenthesis matches the most recent left parenthesis
int isMatchingPair(char left, char right) {
  if (left == '(' && right == ')') {
    return 1;
  } else if (left == '[' && right == ']') {
    return 1;
  }
  return 0;
}

int isExpressionMatch(char* expression) {
  Stack stack;
  initStack(&stack);

  for (int i = 0; expression[i] != '\0'; i++) {
    char c = expression[i];
    if (c == '(' || c == '[') {
      push(&stack, c);
    } else if (c == ')' || c == ']') {
      if (isStackEmpty(&stack) || !isMatchingPair(pop(&stack), c)) {
        return 0;
      }
    }
  }

  return isStackEmpty(&stack);
}

int main() {
  char *expression = NULL;

  printf("Enter an expression: \n");

  size_t buffer_size = 128;
  expression = (char *)malloc(buffer_size);

  if (expression == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  if (scanf("%s", expression) != 1) {
    printf("Failed to read the expression\n");
    return 0;
  }

  free(expression);

//  char expression[128] = "([()]))";
  printf("%s", expression);
  if (isExpressionMatch(expression)) {
    printf("\nThe expression is valid.\n");
  } else {
    printf("\nThe expression is not valid.\n");
  }

  return 0;
}
