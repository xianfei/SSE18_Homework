#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



void Get_yuan(char*, char*, int len);

int main()
{
    int i = 0;
    char receiver[100] = "";
    char s[] = "Life is short, I use Python.";
    int len = strlen(s);
    Get_yuan(receiver, s, len);
    while (receiver[i] != '\0')
    {
        printf("%c", receiver[i]);
        i++;
    }


    system("pause");
    return EXIT_SUCCESS;
}
void Get_yuan(char* receiver, char* src, int len)//获取元音字母
{
    for (int i = 0; i < len; i++)
    {
        char c = src[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        {

            *receiver = c;
            receiver++;//移位
        }
    }

}