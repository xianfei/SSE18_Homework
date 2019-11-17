#include <stdlib.h>
#include <stdio.h>

typedef int ElemType;
#define Status int
#define OK 1
#define ERROR -1

typedef struct node {
    ElemType data;
    struct node *next, *prior;
} DuLinklist;

// 初始化双链表
Status initDuLinklist(DuLinklist *ls) {
    ls->prior = ls;
    ls->next = ls;
    ls->data = 0;
    return OK;
}

// 插入元素
Status insertElem(DuLinklist *ls, int num, ElemType data) {
    for (int i = 0; i < num-1; i++, ls = ls->next)if (!ls->next)return ERROR;
    DuLinklist* node=malloc(sizeof(DuLinklist));
    node->next=ls->next;
    ls->next=node;
    node->next->prior=node;
    node->data=data;
    return OK;
}

// 删除元素
Status deleteElem(DuLinklist *ls, int num){
    for (int i = 0; i < num-1; i++, ls = ls->next)if (!ls->next)return ERROR;
    DuLinklist* willDel=ls->next;
    ls->next=ls->next->next;
    ls->next->prior=ls;
    free(willDel);
    return OK;
}

int main() {
    DuLinklist ls;
    // 初始化双链表
    initDuLinklist(&ls);
    // 插入10个元素分别为9-0
    for(int i=0;i<10;i++)insertElem(&ls,1,i);
    // 删除第五个元素
    deleteElem(&ls,5);
    //输出
    ls = *(ls.next);
    for (int i = 0; i < 9; i++, ls = *(ls.next))printf("%d ",ls.data);
}