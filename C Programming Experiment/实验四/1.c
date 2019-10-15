#include <stdio.h>
//#include <math.h>

int main() {

    char d[1000];
    int a,yw, kg, sz, qt;
    gets(d);
    for(a=0;a<1000;a++){
        if(d[a]==0)break;
        if(d[a]==32){kg++;}
        else if((d[a]<=90&&d[a]>=65)||(d[a]<=122&&d[a]>=97)){yw++;}
        else if(d[a]<=57&&d[a]>=48){sz++;}
        else {qt++;}
    }
    printf("%d %d %d %d",kg,yw,sz,qt);
}
