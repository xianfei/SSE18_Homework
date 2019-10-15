#include <stdio.h>
#define row 3 //数组行数
#define col 3  //数组列数

int main()
{
    int s[row][col]={{5,6,88},{6,4,105},{15,12,18}};
    int max[col],min[row],i,j,exist=0;
    //寻找行中最大
    for(i=0;i<col;i++)
    {
        max[i]=s[i][0];
        for(j=0;j<row;j++){
            max[i]=s[i][j]>max[i]?s[i][j]:max[i];
        }
    }
    //寻找列中最小
    for(i=0;i<col;i++)
    {
        min[i]=s[0][i];
        for(j=0;j<row;j++){
            min[i]=s[j][i]<min[i]?s[j][i]:min[i];
        }
    }
    //判断是否为鞍点
    for(i=0;i<col;i++)
    {
        for(j=0;j<row;j++){
            if((s[i][j]==max[i])&&(s[i][j]==min[j])){printf("The row %d column %d is ANDIAN",i+1,j+1);exist=1;}
        }
    }
    if(exist==0)printf("Can't found ANDIAN");
    return 0;
}




