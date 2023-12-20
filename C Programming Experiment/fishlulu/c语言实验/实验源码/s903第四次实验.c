#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAXSIZE 20
#define ERROR 0;
#define OK 1;
typedef int ElemType;
typedef int Status;//状态用数字表示 OK = 1,ERROR = 0
typedef struct Node
{
	ElemType data;//数据域
	struct Node* Next;//指针域
} Node;

typedef Node* LinkList;//链、指针 

typedef struct Delegate
{
    int No;
    char Name[21];
    int Hour;
    int Number;
	int is_exist;

} Delegate;
int main()
{
	Delegate list[MAXSIZE];//白纸
	for (int k = 0; k < MAXSIZE; k++)
	{
		list[k].is_exist = 0;//初始化所有委托为无
	}
    
	int i;
	int n = 0;//序号
	int temp;

	int temp_No;
	char temp_Name[21];
	int temp_Hour;
	int temp_Number;
	while (1)
	{
		printf("请选择您要执行的操作(0-3)\n");
		printf("\n0:退出\n1:添加订单\n2:修改订单\n3:完成订单(取消订单)\n4:查看订单\n");
		printf("\n您选择要执行的操作是： \n");
		scanf("%d", &i);
		printf("\n");
		switch (i)
		{
		case 0: exit(i); break;
		case 1:
			printf("请输入姓名，时间（小时0-23），人数(例如: 禄禄鱼 0 1 表示禄禄鱼在0点一个人来店吃饭)\n");
			scanf("%s%d%d", list[n].Name, &list[n].Hour, &list[n].Number);
			if (list[n].Hour >= 24 || list[n].Hour < 0)
			{
				printf("输入有误\n");
				continue;
			}
			else if (n >= MAXSIZE) { printf("序号已满，请重启程序清空"); }
			else { list[n].is_exist = 1; list[n].No = n; n++;   continue; }

			break;
		case 2:
			

			printf("需要修改的订单序号\n ");
			scanf("%d", &temp);
			if (temp < MAXSIZE && temp >= 0 && list[temp].is_exist == 1)
			{
				printf("请输入姓名，时间（小时0-23），人数(例如: 禄禄鱼 0 1 表示禄禄鱼在0点一个人来店吃饭)\n");
				scanf("%s%d%d",&temp_Name, &temp_Hour, &temp_Number);
				if (list[temp].Hour >= 24 || list[temp].Hour < 0)
				{
					printf("输入有误\n");
					continue;
				}
				else { list[temp].is_exist = 1; 
					strcpy(list[temp].Name, temp_Name); 
					list[temp].Hour = temp_Hour; 
					list[temp].Number = temp_Number; }
				printf("修改完成\n");
				continue;
			}
			else {
				printf("\n\n\t找不到该订单请核对信息\n\n\n\n\n");
				continue;
			}
			break;
		case 3:
			printf("请输入完成的订单序号:\n");
			scanf("%d\n", temp);
			if (list[temp].is_exist == 1) { list[temp].is_exist = 0; }
			else { printf("不存在该订单\n"); }
			continue;
			break;
		case 4:
			printf("\n\t______________________________________________________\n");
			for (int k = 0; k < MAXSIZE; k++)
			{
				
				if (list[k].is_exist == 1)
				{
					
					printf("序号 : %d\n", list[k].No);
					printf("姓名 : %s\n", list[k].Name);
					printf("时间（小时） : %d\n", list[k].Hour);
					printf("人数 : %d\n", list[k].Number);
					printf("\t______________________________________________________\n");
				}

			}
			continue;
			break;
		default:
			printf("\n\n\t输入错误，请重新输入\n\n\n\n");
			continue;
		}
	}




    system("pause");
    return EXIT_SUCCESS;
}




Status ListInsert(LinkList* L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)
	{
		p = p->Next;
		j++;
	}
	if (!p || j > i) return ERROR;

	s = (LinkList)malloc(sizeof(Node));
	s->data = e;//如果内存不足则s可能是空指针，因此IDE产生警告
	s->Next = p->Next;
	p->Next = s;

	return OK;


}