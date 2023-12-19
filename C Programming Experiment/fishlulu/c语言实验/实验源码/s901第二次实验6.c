#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

float func(float x, int n);
int main()
{
    float x;
    int n;
    printf("请输入x，n的值");
    if (scanf("%f%d", &x, &n) == 2)
    {
        printf("f(%f,%d)的结果为: %f", x, n, func(x, n));
    }
    else printf("传入参数有误");
    system("pause");
    return EXIT_SUCCESS;
}   

float func(float x, int n)
{
    if (n == 1) return sqrt(1 + x);
    else if (n > 1) return sqrt(n + func(x, n - 1));
    else return 0;
}