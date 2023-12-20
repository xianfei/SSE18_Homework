#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int length = 10;
int main_s901_01()
{
    int arr[10];
    for (int i = 0; i < length; i++)
    {   
        printf("请输入第%d个数字", i + 1);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < length-1; i++)
    {
        for (int j = i+1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
    }
    for (int  i = 0; i < length; i++)
    {
        printf("%d  ", arr[i]);
    }
    

    system("pause");
    return EXIT_SUCCESS;
}