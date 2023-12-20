#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define LEN 12
void Reverse(int *arr,int len,int*ret)
{
    int* ptr = arr + len - 1;
    for (int i = 0; i < len; i++)
    {
        ret[i] = *ptr;
        ptr--;
    }

}
int main()
{
    int arr[LEN] = { 1,3,0,4,2,6,1,2,1,0,1,2};//测试数组
    printf("测试数组为\n");
    for (int i = 0; i < LEN; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int ret[LEN] = { 0 };
    Reverse(arr,LEN,ret);
    printf("反转后的数组\n");
    for (int i = 0; i < LEN; i++)
    {
        printf("%d ", ret[i]);
    }





    system("pause");
    return EXIT_SUCCESS;
}