#include <stdio.h>

int main()
{
    char s[3][81];
    int i,k,kg,sz,qt,dx,xx;
    for (i=0;i<3;i++) gets(s[i]);
    for (i=0;i<3;i++){
        for (k=0;k<81;k++){
        if(s[i][k]==0)break;
        if(s[i][k]==32){kg++;}
        else if(s[i][k]<=90&&s[i][k]>=65){dx++;}
        else if(s[i][k]<=122&&s[i][k]>=97){xx++;}
        else if(s[i][k]<=57&&s[i][k]>=48){sz++;}
        else {qt++;}
    }}
    printf("numbers:%d  lower:%d  upper:%d  space:%d  others:%d",sz,xx,dx,kg,qt);
    return 0;
}




