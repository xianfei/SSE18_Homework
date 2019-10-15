#include <stdio.h>

void input(char name[10][10], long num[10])
{
    for (int i = 0; i < 2; i++)
    {
        printf("Please input ID for No.%d :", i + 1);
        scanf("%ld", &num[i]);
        printf("Please input Name for No.%d :", i + 1);
        scanf("%s", &name[i][0]);
        printf("%s,%s,%s\n",name[i],&name[i][0],&name[i]);
        //gets(name[i]);
    }
}

void paixu(char name[10][10], long num[10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (num[j] > num[j + 1])
            {
                long tempnum = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tempnum;
                char tempname;
                for (int q = 0; q < 10; q++)
                {
                    tempname = name[j][q];
                    name[j][q] = name[j + 1][q];
                    name[j + 1][q] = tempname;
                }
            }
        }
    }
}

void search1(char name[10][10], long num[10], long src)
{
    int start = src > num[4] ? 5 : 0;
    for (int i = start; i < start + 5; i++)
    {
        if (src == num[i])
        {
            printf("ID:");
            printf("%ld", num[i]);
            printf("\tName:");
            puts(name[i]);
            puts("\n");
        }
    }
}
int main()
{
    char name[10][10];
    long num[10];
    input(name, num);
    paixu(name, num);
    printf("Please input the ID you want to search:");
    long int src;
    scanf("%ld", &src);
    search1(name, num, src);
    return 0;
}
