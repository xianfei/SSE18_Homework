#include <stdio.h>

int main()
{
    char a;
    printf("输入一个小写的字母：");
    putchar(a = getchar() - 32);
    printf("\n%d",a);
    return 0;
}
