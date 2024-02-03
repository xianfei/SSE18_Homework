//
// Created by 86130 on 2023/9/24.
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define MAX_NAME_SPACE 20

typedef struct Position{
    int x;
    int y;
};
typedef struct City{
    char name[MAX_NAME_SPACE];
    Position pos;
};

typedef City Elem;

typedef struct Node {
    Elem* data;
    struct Node *next;
} Node;

typedef struct Node* LinkList;

typedef int Status;

//��������
LinkList list_create();
int getLength(LinkList L);
Status list_insert(LinkList L, const char *name, int x, int y);
Status list_delete_by_name(LinkList L, const char* name);
Status list_search_by_name(LinkList L, const char* name);
Status list_search_by_distance(LinkList L,int posx,int posy,int distance);

//Status list_merge(LinkList A,LinkList B);
int main(){
    //������������,���ȷֱ�Ϊ3��2,����������
    LinkList A = list_create();
    LinkList B = list_create();
    //��A��B��������ƴ����һ��,�������е�Ԫ�ذ��Ӵ�С˳������
//    list_merge(A,B);


    //��ӳ����Լ���Ӧ����
    list_insert(A, "����", 100, 150);
    list_insert(A, "�Ϻ�", 50, 60);
    list_insert(A, "�Ͼ�", 114, 22);
    //���д����,ͬ������A����,����x,y��Ϊ������200�����������,�Ҳ��ܺ�����ĳ��������ظ�,�����ظ�
    list_insert(A, "����", 10, 120);
    list_insert(A, "����", 20, 130);
    list_insert(A, "����", 35, 140);
    list_insert(A, "����", 46, 120);
    list_insert(A, "��ͨ", 57, 130);

    //���A�����е�Ԫ��
    LinkList p = A->next;
    printf("==========��������==========\n");
    while (p) {
        printf("����: %s,����:(%d,%d)\n",p->data->name,p->data->pos.x,p->data->pos.y);
        p = p->next;
    }
    printf("\n\n\n");
    printf("==========ɾ���Ͼ�==========\n");
    list_delete_by_name(A,"�Ͼ�");
    printf("\n\n\n");
    printf("==========�����Ͼ�==========\n");
    list_search_by_name(A,"�Ͼ�");
    printf("\n\n\n");
    printf("==========���ұ���==========\n");
    list_search_by_name(A,"����");
    printf("\n\n\n");
    printf("==========���Ҿ���(100,150)С�ڵ���50�ĳ���==========\n");
    list_search_by_distance(A,100,150,50);



}

//�й�����Ĳ���

//����һ��������
LinkList list_create(){
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

//��ȡlength
int getLength(LinkList L) {
    int length = 0;
    LinkList p = L->next;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}
//ͷ�巨��������
Status list_insert(LinkList L, const char* name, int x, int y) {
    Position* pos = (Position*)malloc(sizeof(Position));
    Elem* e = (Elem*)malloc(sizeof(Elem));


    Node* p = (Node*)malloc(sizeof(Node));
    if(pos == NULL || e == NULL || p == NULL){
        free(pos);
        free(e);
        free(p);
        return ERROR;
    }
    //�ṹ�帳ֵ
    pos->x = x;
    pos->y = y;
    strcpy((e->name),name);
    e->pos = *pos;
    //����ͷ�����
    p->data = e;
    p->next = L->next;
    L->next = p;
    return OK;
}

Status list_delete_by_name(LinkList L, const char *name) {
    Node* cur = L->next;
    Node* pre = L;
    if(cur == NULL){
        printf("�����˿ձ�\n");
        return ERROR;
    }
    while (cur) {
        if(strcmp(cur->data->name,name)==0)
        {
            printf("��ɾ������: %s,����:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
            pre->next = cur->next;
            free(cur);
            return OK;
        }
        pre = cur;
        cur = cur->next;
    }
    printf("û���ҵ���ɾ���Ķ�Ӧ����\n");
    return ERROR;
}

//A��B��������ƴ����һ��,�������е�Ԫ�ذ��Ӵ�С˳������
//Status list_merge(LinkList A,LinkList B){
//    //ͳ��A��B�ܳ���,��˳�㽫A��B��������
//    int length = 0;
//
//    Node* cur = A->next;
//    while (cur) {
//        length++;
//        if(cur->next!=NULL)
//        {
//            cur = cur->next;
//        }
//        else{
//            (*cur).next = B->next;
//            break;
//        }
//    }
//    if(B->next!=NULL)
//    {
//        cur = B->next;
//
//        while(cur)
//        {
//            if(cur->next!=NULL)
//            {
//                length++;
//                cur = cur->next;
//
//            }
//            else
//            {
//                break;
//            }
//
//        }
//        length++;
//    }
//    //�����־:A���ȱ������
//    std::cout<<"���ȱ������"<<std::endl;
//
//
//    if(length==0){
//        return ERROR;
//    }
//    //��������
//    Elem* arr = (Elem*)malloc(sizeof(Elem)*length);
//    //�������е�Ԫ�ش�������
//    cur = A->next;
//    for (int i = 0; i < length; ++i) {
//        arr[i] = cur->data;
//        cur = cur->next;
//    }
//    //ð������
//    for (int i = 0; i < length; ++i) {
//        for (int j = 0; j < length-i-1; ++j) {
//            if(arr[j]<arr[j+1])
//            {
//                Elem temp = arr[j];
//                arr[j] = arr[j+1];
//                arr[j+1] = temp;
//            }
//        }
//    }
//    //�������е�Ԫ�ش�������
//    cur = A->next;
//    for (int i = 0; i < length; ++i) {
//        cur->data = arr[i];
//        cur = cur->next;
//    }
//    std::cout<<"�������"<<std::endl;
//    return OK;
//
//}
Status list_search_by_name(LinkList L, const char* name) {
    Node* cur = L->next;
    if(cur == NULL){
        printf("�����˿ձ�\n");
        return ERROR;
    }
    while (cur) {
        if(strcmp(cur->data->name,name)==0)
        {
            printf("����: %s,����:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
            return OK;
        }
        cur = cur->next;
    }
    printf("û���ҵ���Ӧ�ĳ���\n");
    return ERROR;
}
Status list_search_by_distance(LinkList L,int posx,int posy,int distance)
{
    Node* cur = L->next;
    if(cur == NULL)
    {
        printf("�����˿ձ�\n");
        return ERROR;
    }
    //�������о�����������������С��distance�ĳ���
    int count=0;
    while (cur) {
        //��������ƽ��+��������ƽ��<distance*distance
        if((cur->data->pos.x-posx)*(cur->data->pos.x-posx)+(cur->data->pos.y-posy)*(cur->data->pos.y-posy)<=distance*distance)
        {
            count++;
            printf("����: %s,����:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
        }
        cur = cur->next;

    }
    if(count == 0)
    {
        printf("û���ҵ���Ӧ�ĳ���\n");
        return ERROR;
    }
    printf("���ҵ�%d������\n",count);
    return OK;
}