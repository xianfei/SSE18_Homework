#include <stdio.h>

int yuanyin(char s[100]) {
    char ns[100];
    int i,j=0;
    for(i=0;s[i]!='\0';i++)
    {
        switch(s[i]){
            case 'a' :case 'e' :case 'i' :case 'o' :case 'u' :
            case 'A' :case 'E' :case 'I' :case 'O' :case 'U' :
                ns[j]=s[i];j++;break;
        }
    }
    ns[j]='\0';
    puts(ns);
}

int main() {
    char s[100];
    gets(s);
    yuanyin(s);
}




