#include <stdio.h>

int main()
{
    int i,j,temp,m;
    int a[11]={23,26,28,29,31,35,37,39,44,45};

    for(i=0;i<10;i++) printf("%d  ",a[i]);
    printf("\n");
    scanf("%d",&a[10]);
    for(i = 0; i < 11 -1; i++)
    {
        m = i;
        for(j = i + 1; j < 11; j++)
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
    for(i=0;i<11;i++)
        printf("%d  ",a[i] );
    printf("\n");
}






