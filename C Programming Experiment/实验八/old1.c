#include <stdio.h>

int notallzero(int* a, int n)
{
    int i;
    for (i = 0; i < n; i++) if (*(a+i)) return 1;
    return 0;
}

int main()
{
    int a[100] = {0}, n, i, leave, j = 0;
    printf("Please input number:");
    scanf("%d", &n);
    for (i = 0; i < n; i++) *(a+i) = i + 1;
    for (i = -1; notallzero(a, n);)
    {
        i++;
        if (i == n) i = 0;
        if (*(a+i) == 0) continue;
        j++;
        if (j == 3) j = 0;
        if (j == 0) *(a+i) = 0;
        if (*(a+i)) leave = *(a+i);
    }
    printf("%d\n", leave);
}