#include <stdio.h>

int main()
{
    int i,j,temp,m;
    int a[10];
    for(i=0;i<10;i++)
        scanf("%d",&a[i]);
    for(i = 0; i < 10 -1; i++)
    {
        m = i;
        for(j = i + 1; j < 10; j++)
        {
            if(a[j] < a[m])
                m = j;
        }
        if(m != i)
        {
            temp = a[i];
            a[i] = a[m];
            a[m] = temp;
        }
    }
    for(i=0;i<10;i++)
        printf("%d  ",a[i] );
    printf("\n");
}



