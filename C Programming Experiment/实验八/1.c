#include<stdio.h>

int maopao(int *a,int b){
    int j ,i ,temp;
    for(j=0;j<b;j++)
    {
        for (i=0;i<b-1-j;i++)
            if (a[i]>a[i+1])
            {
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
    }
}
int main()
{
    int a[] = {4,2,7,5,9,1,3};
    int num = 7,i;
    maopao(a,num);
    for(i=0;i<num;i++)printf("%d",*(a+i));
    return 0;
}
