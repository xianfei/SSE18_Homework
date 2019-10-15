#include <stdio.h>
//#include <math.h>

int main() {
    int a,b,c;
    for(a=1;a<10000;a++){
        c =a ;
        for(b=1;b<10;b++){
        if(c%2==0&&c>0){
            c=c-(c/2)-1;
        }else{
            c = 0;
            break;

        }}
        if(c==1){printf("%d\n",a);}
    }
}

