#include <stdio.h>

void tos(int n)
{
    int i;
    char c;
    if (i = n / 10)
        tos(i);
    c = n % 10 + '0';
    putchar(c);
}

int main()
{
    int num;
    printf("Input:");
    scanf("%d", &num);
    printf("Output:");
    tos(num);
}
