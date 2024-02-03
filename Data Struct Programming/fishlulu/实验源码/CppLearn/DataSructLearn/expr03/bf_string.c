#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//BF算法,失败返回0,成功返回匹配的位置,从1开始
int BF_search(char* S,char* T)//S:源字符串,T目标字符串
{
  //用于连续寻找的临时指针
  char* tS = S;
  char* tT = T;
  int i = 1;//用于记录匹配的位置
  while (*S != '\0')
  {
    if (*S == *T)//首字符匹配上的话
    {
      tT = T;
      tS = S;//主串指针会回退，这就导致了暴力算法效率低下
      while (tT != '\0')//开始连续匹配
      {
        if (*tT == *tS)
        {
          tT++;
          tS++;
        }
        else //中断循环
        {
          S++;
          i++;
          break;
        }

        if (*tT == '\0') return i;
      }

    }
    else
    {
      S++;
      i++;
    }

  }
  return 0;

}

//编写bf算法测试函数
int main() {
  char *S = "this is a source string to be tested";
  char *T = "source";
  int result = BF_search(S, T);
  if(result == 0) printf("Not Found\n");
  else{
    printf("Found\n");
    printf("at position %d of source string\n", result);

  }
}