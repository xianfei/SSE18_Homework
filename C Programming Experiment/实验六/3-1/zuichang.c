#include <stdio.h>

int zuichang(char s[]) {
    char s2[100];
    int i,j=0,maxlen=0;
    //找出最长的单词
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]==' ')
        {
            for(j=0;j<=100;j++)s2[j]=0;
            j=0;
            continue;}
        else{s2[j]=s[i];j++;maxlen=j>maxlen?j:maxlen;}
    }
    //输出最长的单词
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]==' ')
        {
            for(j=0;j<=100;j++)s2[j]=0;
            j=0;
            continue;}
        else{s2[j]=s[i];j++;}
        if(j==maxlen)printf("%s",s2);
    }

}
