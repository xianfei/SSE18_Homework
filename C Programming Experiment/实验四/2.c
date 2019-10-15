#include <stdio.h>
//#include <math.h>

int main() {


    int a;

    for(a=100;a<1000;a++){
        if((a/100)*(a/100)*(a/100)+((a-(a/100)*100)/10)*((a-(a/100)*100)/10)*((a-(a/100)*100)/10)+(a%10)*(a%10)*(a%10)==a){
            printf("%d\n",a);
        }
    }
}
