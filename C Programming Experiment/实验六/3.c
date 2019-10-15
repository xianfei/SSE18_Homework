#include <stdio.h>
#include <ctype.h>

int zuichang(char s[]) {
    char s2[1000];
    int i,j=0,maxlen=0;
    //找出最长的单词的长度
    for(i=0;s[i]!='\0';i++)
    {
        if(!(isalpha(s[i])))
        {
        for(j=0;j<1000;j++)s2[j]=0;
        j=0;}
        else{s2[j]=s[i];j++;maxlen=j>maxlen?j:maxlen;}
    }
    //输出最长的单词
    j=0;
    for(i=0;s[i]!='\0';i++)
    {
        if(!(isalpha(s[i])))
        {
            for(j=0;j<1000;j++)s2[j]=0;
            j=0;}
        else{s2[j]=s[i];j++;}
        if(j==maxlen)printf("最长的单词是%s\n",s2);
    }
    return 0;
}

int main() {
    char s[1000];
    gets(s);
    zuichang(s);
    return 0;
}




