#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void DateCalc(int year, int day,int* is_run,int** dayTab,int *ret1,int* ret2)//计算对应月份日期
{
    int month = 0;
    int day_calc = 0;
    if (year % 4 == 0 && year % 100 != 0)//如果是闰年的话
    {
        *is_run = 1;
        dayTab += 1;//转到闰年计算
    }
    //printf("%d\n", **dayTab);
    while (day - **dayTab > 0&&month< 12)
    {
        day -= **dayTab;
        *dayTab += 1;
        month += 1;
    }
    day_calc = day;//最后剩下的天数为该月日期
    //指针接收结果
    *ret1 = month;
    *ret2 = day_calc;
}


int main()
{
    //非闰年,闰年每个月的天数

    int year = 0;
    int day = 0;
    int year_ret, day_ret;
    int is_run = 0,*p1 = &is_run;
    int* ret1 = &year_ret;
    int* ret2 = &day_ret;

    int** dayTab = (int**)malloc(sizeof(int*) * 2);
    for (int i = 0; i < 2; i++)
    {
        dayTab[i] = (int*)malloc(sizeof(int*) * 13);
    }
    int t1[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int t2[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    dayTab[0] = t1;
    dayTab[1] = t2;
   

    printf("请输入年份和第几天:\n");
    scanf("%d", &year);
    scanf("%d", &day);
    //printf("%d %d", year, day);
    printf("%d年的第%d天,日期是:\n",year,day);
    DateCalc(year, day, p1,dayTab, ret1, ret2);
    if(*ret1 && *ret2) printf("%d年%d月%d日\n", year, *ret1, *ret2);
    
    printf("该年份");
    if (is_run == 1) printf("是闰年\n");
    else printf("不是闰年\n");
    system("pause");
    return EXIT_SUCCESS;
}