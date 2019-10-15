#include<stdio.h>
#include<math.h>

int input(double data[100][4]){
    int i,j;
    puts("请输入学生的学号及成绩信息，输入任意字母来结束");
    for(i=0;1;i++){
        for(j=0;j<3;j++){
            switch(j){
                case 0:printf("请输入第%d位学生的学号\n",i + 1);break;
                case 1:printf("请输入第%d位学生的平时成绩\n",i + 1);break;
                case 2:printf("请输入第%d位学生的期末成绩\n",i + 1);break;
            }
            if (!(scanf("%lf",&data[i][j]))) return i;
        }
    }
}

void zongpingchengji(double data[100][4],double a,double b,int num){
    int i;
    for(i=0;i<num;i++)data[i][3]=(data[i][1]*a+data[i][2]*b)/100;
}

void output(double sheet[6][5],double* pingjunfen,double* biaozhuncha){
    int i;
    puts("分类\t\t项目\t\t不及格\t60~69分\t70~79分\t80~89分\t90~100分\t平均分\t标准差\t");
    printf("平时成绩\t人数\t\t");
    for(i=0;i<5;i++)printf("%d\t\t",(int)sheet[0][i]);
    printf("%.2lf\t%.2lf\n",pingjunfen[0],biaozhuncha[0]);
    printf("\t\t比例\t\t");
    for(i=0;i<5;i++)printf("%d%%\t\t",(int)sheet[1][i]);
    printf("\n期末成绩\t人数\t\t");
    for(i=0;i<5;i++)printf("%d\t\t",(int)sheet[2][i]);
    printf("%.2lf\t%.2lf\n",pingjunfen[1],biaozhuncha[1]);
    printf("\t\t比例\t\t");
    for(i=0;i<5;i++)printf("%d%%\t\t",(int)sheet[3][i]);
    printf("\n总评成绩\t人数\t\t");
    for(i=0;i<5;i++)printf("%d\t\t",(int)sheet[4][i]);
    printf("%.2lf\t%.2lf\n",pingjunfen[2],biaozhuncha[2]);
    printf("\t\t比例\t\t");
    for(i=0;i<5;i++)printf("%d%%\t\t",(int)sheet[5][i]);
}
void tongji(double data[100][4],double sheet[6][5],int num,double* pingjunfen,double* biaozhuncha){
    int i,j;
    double avgsum=0,bzcsum=0;
    for(i=1;i<4;i++){//i为统计的项目
        avgsum=0;
        bzcsum=0;
        for(j=0;j<num;j++){
            switch((int)(data[j][i]/10)){
                case 10:
                case 9:sheet[i*2-2][4]++;break;
                case 8:sheet[i*2-2][3]++;break;
                case 7:sheet[i*2-2][2]++;break;
                case 6:sheet[i*2-2][1]++;break;
                default:sheet[i*2-2][0]++;break;
            }
            avgsum += data[j][i];
        }
        for(j=0;j<5;j++)sheet[i*2-1][j]=(sheet[i*2-2][j]/num)*100;
        pingjunfen[i-1]=avgsum/num;
        for(j=0;j<num;j++)bzcsum += (data[j][i]-pingjunfen[i-1])*(data[j][i]-pingjunfen[i-1]);
        biaozhuncha[i-1]=sqrt(bzcsum/num);
    }
}
int main() {
    //output();
    double data[100][4]={0},sheet[6][5]={0},pingjunfen[3]={0},biaozhuncha[3]={0};
    int num,i;
    double max=0,min=100;
    double pingshibili,qimobili;
    puts("请输入平时成绩所占比例百分比");
    scanf("%lf",&pingshibili);
    puts("请输入期末成绩所占比例百分比");
    scanf("%lf",&qimobili);
    num = input(data);
    zongpingchengji(data,pingshibili,qimobili,num);
    tongji(data,sheet,num,pingjunfen,biaozhuncha);
    output(sheet,pingjunfen,biaozhuncha);
    for(i=0;i<num;i++){
        max = data[i][2]>max?data[i][2]:max;
        min = data[i][2]<min?data[i][2]:min;
    }
    printf("\n期末考试卷面及格率：%.2lf%%\t",100-sheet[3][0]);
    printf("期末考试卷面最高分：%.2lf\t",max);
    printf("期末考试卷面最低分：%.2lf\n",min);
    printf("总评=平时X%.2lf%%+考试X%.2lf%%\t",pingshibili,qimobili);
    printf("学生总人数：%d\n",num);
}