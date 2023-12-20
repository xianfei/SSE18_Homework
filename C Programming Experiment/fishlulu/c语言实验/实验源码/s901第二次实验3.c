#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <string.h>

int main_s901_03()
{
    char s[81];
    printf("请输入你的一句话");
    gets(s);
    int count = 0;
    int flag = 0;

    for (int i = 0; s[i] != '\0';i++)
    {
        
        if (s[i] == ' ') flag = 0;
        else if (flag == 0) { flag = 1; count++; }
    }

    printf("%d\n", count);



    system("pause");
    return EXIT_SUCCESS;
}
