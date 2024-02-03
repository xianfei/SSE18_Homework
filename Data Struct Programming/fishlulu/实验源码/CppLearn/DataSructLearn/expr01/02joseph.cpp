#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


//二乔问题：密码版

typedef struct node
{
    int data;
    struct node* next;
    int num;
} node;

node* create(int* codeset, int length)
{

    node *p = NULL, *head;
    head = (node*)malloc(sizeof(node));
    p = head;
    node* s;
    s = NULL;
    int i = 1;

    if (length != 0)
    {


        while (i <= length)
        {
            s = (node*)malloc(sizeof(node));
            s->data = codeset[i - 1];
            s->num = i++;
            p->next = s;
            p = s;
        }
        s->next = head->next;//最后一个元素指向第一个元素，头结点只是个工具，用完就可以扔了
    }
    free(head);

    return s->next;//返回第一个节点
}

int joseph_solution(int* codeset,int ini_code)
{
    node* p = create(codeset, 7);
    node* temp;

    int flag = ini_code;//指示顺序报数到第几个数
    int num = 1;
    while (p != p->next)
    {

        while (num < flag - 1)
        {
            p = p->next;
            num++;
        }

        printf("%d->", p->next->num);
        flag = p->next->data;
        num = 1;
        temp = p->next;
        p->next = temp->next;
        free(temp);
        p = p->next;
    }

    printf("%d\n",p->num);
}
int main()
{

    int codeset[7] = {3,1,7,2,4,8,4};
    joseph_solution(codeset,20);
    system("pause");
    return EXIT_SUCCESS;
}



