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

//函数声明
LinkList list_create();
int getLength(LinkList L);
Status list_insert(LinkList L, const char *name, int x, int y);
Status list_delete_by_name(LinkList L, const char* name);
Status list_search_by_name(LinkList L, const char* name);
Status list_search_by_distance(LinkList L,int posx,int posy,int distance);

//Status list_merge(LinkList A,LinkList B);
int main(){
    //创建两个链表,长度分别为3和2,存放随机数字
    LinkList A = list_create();
    LinkList B = list_create();
    //将A和B两个链表拼接在一起,并将其中的元素按从大到小顺序排列
//    list_merge(A,B);


    //添加城市以及对应坐标
    list_insert(A, "北京", 100, 150);
    list_insert(A, "上海", 50, 60);
    list_insert(A, "南京", 114, 22);
    //多编写几个,同样放在A表中,坐标x,y均为不超过200的随机正整数,且不能和上面的城市名字重复,坐标重复
    list_insert(A, "杭州", 10, 120);
    list_insert(A, "苏州", 20, 130);
    list_insert(A, "无锡", 35, 140);
    list_insert(A, "常州", 46, 120);
    list_insert(A, "南通", 57, 130);

    //输出A链表中的元素
    LinkList p = A->next;
    printf("==========遍历链表==========\n");
    while (p) {
        printf("城市: %s,坐标:(%d,%d)\n",p->data->name,p->data->pos.x,p->data->pos.y);
        p = p->next;
    }
    printf("\n\n\n");
    printf("==========删除南京==========\n");
    list_delete_by_name(A,"南京");
    printf("\n\n\n");
    printf("==========查找南京==========\n");
    list_search_by_name(A,"南京");
    printf("\n\n\n");
    printf("==========查找北京==========\n");
    list_search_by_name(A,"北京");
    printf("\n\n\n");
    printf("==========查找距离(100,150)小于等于50的城市==========\n");
    list_search_by_distance(A,100,150,50);



}

//有关链表的操作

//创建一个空链表
LinkList list_create(){
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

//获取length
int getLength(LinkList L) {
    int length = 0;
    LinkList p = L->next;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}
//头插法插入数据
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
    //结构体赋值
    pos->x = x;
    pos->y = y;
    strcpy((e->name),name);
    e->pos = *pos;
    //链表头插操作
    p->data = e;
    p->next = L->next;
    L->next = p;
    return OK;
}

Status list_delete_by_name(LinkList L, const char *name) {
    Node* cur = L->next;
    Node* pre = L;
    if(cur == NULL){
        printf("传入了空表\n");
        return ERROR;
    }
    while (cur) {
        if(strcmp(cur->data->name,name)==0)
        {
            printf("已删除城市: %s,坐标:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
            pre->next = cur->next;
            free(cur);
            return OK;
        }
        pre = cur;
        cur = cur->next;
    }
    printf("没有找到可删除的对应城市\n");
    return ERROR;
}

//A和B两个链表拼接在一起,并将其中的元素按从大到小顺序排列
//Status list_merge(LinkList A,LinkList B){
//    //统计A和B总长度,并顺便将A和B连接起来
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
//    //输出日志:A长度遍历完毕
//    std::cout<<"长度遍历完毕"<<std::endl;
//
//
//    if(length==0){
//        return ERROR;
//    }
//    //创建数组
//    Elem* arr = (Elem*)malloc(sizeof(Elem)*length);
//    //将链表中的元素存入数组
//    cur = A->next;
//    for (int i = 0; i < length; ++i) {
//        arr[i] = cur->data;
//        cur = cur->next;
//    }
//    //冒泡排序
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
//    //将数组中的元素存入链表
//    cur = A->next;
//    for (int i = 0; i < length; ++i) {
//        cur->data = arr[i];
//        cur = cur->next;
//    }
//    std::cout<<"排序完毕"<<std::endl;
//    return OK;
//
//}
Status list_search_by_name(LinkList L, const char* name) {
    Node* cur = L->next;
    if(cur == NULL){
        printf("传入了空表\n");
        return ERROR;
    }
    while (cur) {
        if(strcmp(cur->data->name,name)==0)
        {
            printf("城市: %s,坐标:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
            return OK;
        }
        cur = cur->next;
    }
    printf("没有找到对应的城市\n");
    return ERROR;
}
Status list_search_by_distance(LinkList L,int posx,int posy,int distance)
{
    Node* cur = L->next;
    if(cur == NULL)
    {
        printf("传入了空表\n");
        return ERROR;
    }
    //查找所有距离给定坐标参数距离小于distance的城市
    int count=0;
    while (cur) {
        //横坐标差的平方+纵坐标差的平方<distance*distance
        if((cur->data->pos.x-posx)*(cur->data->pos.x-posx)+(cur->data->pos.y-posy)*(cur->data->pos.y-posy)<=distance*distance)
        {
            count++;
            printf("城市: %s,坐标:(%d,%d)\n",cur->data->name,cur->data->pos.x,cur->data->pos.y);
        }
        cur = cur->next;

    }
    if(count == 0)
    {
        printf("没有找到对应的城市\n");
        return ERROR;
    }
    printf("共找到%d个城市\n",count);
    return OK;
}