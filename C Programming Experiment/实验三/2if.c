#include <stdio.h>

int main() {
    int x, y;
    scanf ("%d", &x);
    if (x >= 90 & x <= 100 )
    {
        printf("A");
    }
    if (x >= 81 & x <= 89 )
    {
        printf("B");
    }
    if (x >= 71 & x <= 79 )
    {
        printf("C");
    }
    if (x >= 61 & x <= 69 )
    {
        printf("D");
    }
    if (x >= 0 & x <= 60 )
    {
        printf("E");
    }
    if (x < 0 , x >100 )
    {
        printf("Error");
    }
    return 0;
}
