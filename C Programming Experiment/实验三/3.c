#include <stdio.h>

int main()
{
    int i,j,temp;
    int a[4];
    for(i=0;i<4;i++)
        scanf ("%d",&a[i]);
    for(j=0;j<4;j++)
    {
        for (i=0;i<3-j;i++)
            if (a[i]>a[i+1])
            {
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
    }
    for(i=0;i<4;i++)
        printf("%d  ",a[i] );
    printf("\n");
}