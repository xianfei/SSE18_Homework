#include <stdio.h>
#include <string.h>
#define maxnum 100

int n=0;

struct data
{
    char name[20];
    int number;
    char time[10];
}data[maxnum];

void add()
{
    printf("用户姓名:");
    scanf("%s",data[n].name);
    printf("用餐人数:");
    scanf("%d",&data[n].number);
    printf("用餐时间:");
    scanf("%s",data[n].time);
    n++;
}

void search()
{
    int i;
    char name1[20];
    printf("\n请输入需要查询的用户姓名:");
    scanf("%s",name1);
    for(i=0;i<maxnum;i++)
    {
        if(strcmp(data[i].name,name1)==0)
        {
            printf("用餐人数:%d\n",data[i].number);
            printf("用餐时间:%s\n",data[i].time);
            return;
        }
    }
    printf("找不到该用户！\n");
}

void modify()
{
    int i;
    char name1[10];
    printf("请输入修改信息的用户姓名:");
    scanf("%s",name1);
    for(i=0;i<maxnum;i++)
    {
        if(strcmp(data[i].name,name1)==0)
        {
            printf("请输入用餐人数:");
            scanf("%d",&data[i].number);
            printf("请输入用餐时间:");
            scanf("%s",data[i].time);
            printf("修改成功！\n");
            return;
        }
    }
    printf("找不到该用户！\n");
}

void del()
{
    int i;
    char name1[10];
    printf("请输入要删除的用户姓名:");
    scanf("%s",name1);
    for(i=0;i<maxnum;i++)
    {
        if(strcmp(data[i].name,name1)==0)
        {
            strcpy(data[i].name,"\0");
            data[i].number=0;
            strcpy(data[i].time,"\0");
            printf("删除成功！\n");
            return;
        }
    }
    printf("找不到该用户！\n");
}

int main()
{
    int k;
    while(1)
    {
        printf("按0添加预约，按1查找预约，按2修改预约，按3删除预约,按4退出系统\n");
        scanf("%d",&k);
        if(k==0)
            add();
        else if(k==1)
            search();
        else if(k==2)
            modify();
        else if(k==3)
            del();
        else if(k==4)return 0;
        else printf("请重新输入\n");
    }
}
