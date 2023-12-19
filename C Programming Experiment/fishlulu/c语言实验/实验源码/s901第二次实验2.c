#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



int main_s901_02()
{
    int scores[50];//学生分数
    int ret;
    int score;
    int range_1 = 0;
    int range_2 = 0;
    int range_3 = 0;
    int range_4 = 0;
    int range_5 = 0;
    int range_6 = 0;
    int range_7 = 0;
    int range_8 = 0;
    int range_9 = 0;
    int range_10 = 0;
    int range_11= 0;
    for (int i = 0; i < 50; i++)
    {
        ret = rand() % 101;
        scores[i] = ret;
        printf("%d\t", ret);
    }
    printf("\n");
    //建立11个范围
    int ranges[11][50];

    //根据学生分数分组范围
    for (int i = 0; i < 50; i++)
    {
        int n= scores[i] /10;
        if (n<=10)
        {
            switch (n)
            {
            case 0:
                range_1++;
                break;
            case 1:
                range_2++;
                break;
            case 2:
                range_3++;
                break;
            case 3:
                range_4++;
                break;
            case 4:
                range_5++;
                break;
            case 5:
                range_6++;
                break;
            case 6:
                range_7++;
                break;
            case 7:
                range_8++;
                break;
            case 8:
                range_9++;
                break;
            case 9:
                range_10++;
                break;
            case 10:
                range_11++;
                break;

            default:
                break;
            }
        }

    }

    printf("%d %d %d %d %d %d %d %d %d %d %d", range_1, range_2, range_3, range_4, range_5, range_6, range_7, range_8, range_9, range_10, range_11);

    system("pause");
    return EXIT_SUCCESS;
}