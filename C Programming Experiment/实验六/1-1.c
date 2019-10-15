#include <stdio.h>

int panduansushu(int number) {
    int i;
    if(number < 2) return 0;
    for(i = 2; i * i < number; i++)
        if(number % i == 0)
            return 0;
    return 1;
}

int main() {
    int i;
    for(i=100;i<=200;i++){
        if(panduansushu(i))
        {printf("%d  ",i);}
    }
    return 0;
}

