#include <stdio.h>
int main() {
    int i;
    int panduansushu(int i);
    scanf("%d", &i);
    printf("%s", panduansushu(i) ? "true" : "false");
    return 0;
}



int panduansushu(int number) {
    int i;
    if(number < 2) return 0;
    for(i = 2; i * i < number; i++)
        if(number % i == 0)
            return 0;
    return 1;
}

