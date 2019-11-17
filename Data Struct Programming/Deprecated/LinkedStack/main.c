#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR -1
#define Status int
typedef int ElemType;

typedef struct node{
    struct node* prev;
    ElemType data;
}LinklistStack;

Status initLinklistStack(LinklistStack *ls){
    ls->prev=0;
}

Status push(LinklistStack* ls,ElemType e){
    LinklistStack* node=malloc(sizeof(LinklistStack));
    if(!node) return ERROR;
    node->data=e;
    node->prev=ls->prev;
    ls->prev=node;
    return OK;
}

Status pop(LinklistStack* ls,ElemType* e){
    if(!ls->prev)return ERROR;
    *e = ls->prev->data;
    LinklistStack* willDel=ls->prev;
    ls->prev=ls->prev->prev;
    free(willDel);
    return OK;
}

int main() {
    LinklistStack stack;
    // 初始化链表stack
    initLinklistStack(&stack);
    // push 0-199 to stack
    for (int i = 0; i < 200; i++)push(&stack, i);
    int num;
    // pop them
    for (int i = 0; i < 200; i++) {
        pop(&stack, &num);
        printf("%d ", num);
    }
}