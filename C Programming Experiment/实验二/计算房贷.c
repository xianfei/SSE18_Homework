#include <stdio.h>
#include <math.h>

int main()
{
    float d=300000 , p=6000 , r=0.01;
    printf("%5.1f\n",(log10(p)-log10(p-d*r))/log10(1+r));
    return 0;
}
