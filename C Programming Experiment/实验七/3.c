#include <stdio.h>

int isrunnian(int y)
{
    if (y / 100 && y % 4 == 0 || y / 400 == 0)
        return 1;
    else
        return 0;
}

int daynum(int y, int m, int d)
{
    int daymax[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isrunnian(y))
        daymax[2] = 29;
    int day = 0;
    for (int i = m - 1; i; i--)
        day += daymax[i];
    return day + d;
}

int main()
{
    int y, m, d;
    printf("请输入年：");
    scanf("%d", &y);
    printf("请输入月：");
    scanf("%d", &m);
    printf("请输入日：");
    scanf("%d", &d);
    if (isrunnian(y))
        printf("这是个闰年\n");
    else
        printf("这不是闰年\n");
    printf("今年一共过了%d天\n", daynum(y, m, d));
}