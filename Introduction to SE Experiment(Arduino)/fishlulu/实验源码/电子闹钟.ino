#include <IRremote.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

int RECV_PIN = 10;                                                 //定义红外接收的数字引脚口为10号口
int ALARM_PIN = 4;                                                 //定义蜂鸣器的接口为4
IRrecv irrecv(RECV_PIN);
decode_results results;                                        //定义红外接收装置的接收结果变量


/*定义修改位的在液晶屏上的x坐标，
*分别对应Y1,Y2,Y3,Y4,M1,M2,D1,D2,
*H1,H2,MI1,MI2,S1,S2，
*第二行的加上了一个偏移量12
*/
int pos[] = { 3,4,5,6,9,12,
          14,17,20 };

int modifyIndex;

/*
 电源 FD00FF
 vol+    FD807F
 func/stop FD40BF
 左快进 FD20DF
 开始 FDA05F
 右快进 FD609F
 下 FD10EF
 vol- FD906F
 上 FD50AF
 0 FD30CF
 EQ FDB04F
 st/rept FD708F
 1 FD08F7
 2 FD8877
 3 FD48B7
 4 FD28D7
 5 FDA857
 6 FD6897
 7 FD18E7
 8 FD9867
 9 FD58A7
 */

boolean light_flag;                                              //定义lcd屏亮暗标志，true表示亮屏，false表示暗屏
boolean modify_flag;                                             //定义修改时间模式标志位，true表示修改时间模式，false表示非修改时间模式
boolean alarm_flag;                                              //定义设置闹铃模式标志位，true表示设置闹钟模式，false表示非设置闹钟模式
boolean buzzer_flag;


//定义全局时间变量--年 月 日 时 分 秒
int Y1, Y2, Y3, Y4;                                                 //定义年份的四位，从高到低
int M1, M2;                                                       //定义月份的两位，从高到低
int D1, D2;                                                       //定义日期的两位，从高到低
int H1, H2;                                                       //定义小时的两位，从高到低
int MI1, MI2;                                                     //定义分钟的两位，从高到低
int S1, S2;                                                       //定义秒数的两位，从高到低
int Date;                                                        //定义星期
int* h1 = &H1, * h2 = &H2;
int* mi1 = &MI1, * mi2 = &MI2;
int* s1 = &S1, * s2 = &S2;

//定义全局闹铃时间变量--月 日 时 分
int Alarm_M1, Alarm_M2;                                                       //定义月份的两位，从高到低
int Alarm_D1, Alarm_D2;                                                       //定义日期的两位，从高到低
int Alarm_H1, Alarm_H2;                                                       //定义小时的两位，从高到低
int Alarm_MI1, Alarm_MI2;                                                     //定义分钟的两位，从高到低
int Alarm_S1, Alarm_S2;                                                       //定义秒数的两位，从高到低


//定义临时变量存储时间
int temp_Y1, temp_Y2, temp_Y3, temp_Y4;                                                 //定义年份的四位，从高到低
int temp_M1, temp_M2;                                                       //定义月份的两位，从高到低
int temp_D1, temp_D2;                                                       //定义日期的两位，从高到低
int temp_H1, temp_H2;                                                       //定义小时的两位，从高到低
int temp_MI1, temp_MI2;                                                     //定义分钟的两位，从高到低
int temp_Date;                                                        //定义星期
int temp_S1, temp_S2;                                                  //定义秒数的两位，从高到低
int* temp_h1 = &temp_H1, * temp_h2 = &temp_H2;
int* temp_mi1 = &temp_MI1, * temp_mi2 = &temp_MI2;
int* temp_s1 = &temp_S1, * temp_s2 = &temp_S2;

//定义判断闰年的函数
#define ISYEARP(x) x/100!=0&&x%4==0||x/400==0?1:0
//定义每个月的天数
int dayOfMonth[13][2] = {
    0,0,
    31,31,
    28,29,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
};

int x, y;                                                        //定义修改液晶屏的时间数位的横纵坐标




//功能函数定义

void addTime();                                              //定义增加时间的函数，执行结果会使当前光标处的时间数位加一
void minusTime();                                               //定义减少时间的函数，执行结果会使当前光标处的时间数位减一
void setAlarm();                                                //定义设置闹钟的函数
void tita(int* H1, int* H2, int* MI1, int* MI2, int* S1, int* S2);                                                    //定义时间流动函数
void date();                                                    //定义日期的流动函数
void calendarInit();                                            //定义万年历初始化函数
void calendarShow();                                            //定义万年历的显示函数
void xblink();                                                  //定义某一块闪烁的函数
void xNoblink();                                                //定义某一块不闪烁的函数
int getmol(int num, int calc,int AddOrMin)//进行取模运算实现左移右移
{ 
    if (AddOrMin == 0) { return (num + 1) % calc; }
    else return (num + calc - 1) % calc;

}
int WeekCalc(int Y1,int Y2,int Y3,int Y4,int M1,int M2,int D1,int D2)//根据年份日期返回星期
{
    int Date = 0,Y = 0,D = 0;//D为一年内累计的天数
    Y = Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4;
    int day = D1 * 10 + D2;
    for (int i = 1; i < (M1*10 + M2); i++)
    {
        D += dayOfMonth[i][ISYEARP(Y)];
    }
    D += day;//一年累计的天数
    Date = ((Y - 1) + ((Y - 1) / 4) - ((Y - 1) / 100) + ((Y - 1) / 400) + D) % 7;//计算星期公式
    Serial.print("Date = ");
    Serial.print(Date);
    Serial.println(D);
    
    return Date;
}

//初始化函数
void setup() {
    // put your setup code here, to run once:
    modifyIndex = 0;
    x = 3;
    y = 0;
    light_flag = true;
    modify_flag = false;
    alarm_flag = false;
    buzzer_flag = false;
    Serial.begin(9600);
    irrecv.enableIRIn();
    pinMode(ALARM_PIN, OUTPUT);
    lcd.init();
    lcd.backlight();
    calendarInit(); //初始化时间
    calendarShow();
}

void loop() {
    // put your main code here, to run repeatedly:

    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);

        if (results.value == 0xFD00FF) {       //如果接受到的是电源键的信号，万年历亮屏或者息屏
            light_flag = !light_flag;
            if (light_flag)
            {
                buzzer_flag = false;
                lcd.backlight();
            }
            else {
                lcd.noBacklight();
                buzzer_flag = false;
            }
        }

        else if (results.value == 0xFD08F7) {                       //如果接受到的是1信号，则进入修改时间模式或非修改时间模式
            modifyIndex = 0;
            modify_flag = !modify_flag;
            alarm_flag = false;

            if (modify_flag) {
                xblink();
                Serial.print("接受到1信号，进入修改时间模式");
            }
            else {
                xNoblink();
                modifyIndex = 0;
            }
        }

        else if (results.value == 0xFD8877)                        //如果接受的是2信号，则进入设定闹钟模式,或者退出闹钟模式

        {
            if (alarm_flag == false)                                    //进入设定闹钟模式
            {
                temp_Y1 = Y1, temp_Y2 = Y2, temp_Y3 = Y3, temp_Y4 = Y4, temp_M1 = M1, temp_M2 = M2, temp_D1 = D1, temp_D2 = D2, temp_H1 = H1, temp_H2 = H2, temp_MI1 = MI1, temp_MI2 = MI2, temp_S1 = S1, temp_S2 = S2;  //保存设置闹钟前的当前时间
                modify_flag = true;
                buzzer_flag = false;
                x = 2;
                y = 1;                                                    //设置好光标的坐标
                xblink();
                modifyIndex = 6;
                alarm_flag = true;
            }
            else {                                                     //退出闹钟模式
                //保存闹钟变量
                xNoblink();
                modify_flag = false;
                alarm_flag = !alarm_flag;
                setAlarm();
                //恢复时间
                Y1 = temp_Y1, Y2 = temp_Y2, Y3 = temp_Y3, Y4 = temp_Y4, M1 = temp_M1, M2 = temp_M2, D1 = temp_D1, D2 = temp_D2, H1 = temp_H1, H2 = temp_H2, MI1 = temp_MI1, MI2 = temp_MI2, S1 = temp_S1, S2 = temp_S2;
            }
        }

        else if (results.value == 0xFD20DF)                          //如果接收到的是左快进的信号
        {
            if (modify_flag) {
                xNoblink();
                modifyIndex = (modifyIndex + 8) % 9;
                x = pos[modifyIndex];
                if (x > 12) {                                           //如果横坐标到了逻辑上的第二行，则要将其减去偏移量12，并使纵坐标为1
                    x = x - 12;
                    y = 1;
                }
                else {
                    y = 0;
                }
                xblink();
            }
        }

        else if (results.value == 0xFD609F)                               //如果接收到的是右快进信号
        {
            if (modify_flag) {
                xNoblink();
                modifyIndex = (modifyIndex + 1) % 9;
                x = pos[modifyIndex];                          //如果横坐标到了逻辑上的第二行，则要将其减去偏移量12，并使纵坐标为1
                if (x > 12) {
                    x = x - 12;
                    y = 1;
                }
                else {
                    y = 0;
                }
                xblink();
            }
        }

        else if (results.value == 0xFD807F)                           //如果接受到的是vol+信号，则调整当前数位的值加一，值可循环
        {
            if (modify_flag) {
                addTime();
            }
        }

        else if (results.value == 0xFD906F)                           //如果接受到的是vol-信号，则调整当前数位的值减一，值可循环
        {
            if (modify_flag) {
                minusTime();
            }
        }

        irrecv.resume();
    }


    if (modify_flag == false && alarm_flag == false)
    {
        calendarShow();                  //显示时间
        tita(h1,h2,mi1,mi2,s1,s2);
    }
    //calendarShow();
    //tita();
    if (alarm_flag == true) { tita(temp_h1, temp_h2,temp_mi1, temp_mi2, temp_s1, temp_s2); }//解决修改闹钟之后时间不同步的问题
    delay(1000);                      //一秒刷新一次

    if (buzzer_flag) //闹钟响铃
    {
        digitalWrite(ALARM_PIN, HIGH);
    }
    else {
        digitalWrite(ALARM_PIN, LOW);
    }

}

//万年历初始化函数，加串口通信读取电脑当前时间
void calendarInit()
{
    Y1 = 2, Y2 = 0, Y3 = 2, Y4 = 1;                                            //年份初始化
    M1 = 0, M2 = 1;                                                      //月份初始化
    D1 = 0, D2 = 2;                                                      //日期初始化
    H1 = 1, H2 = 4;                                                      //小时初始化
    MI1 = 2, MI2 = 3;                                                    //分钟初始化
    S1 = 3, S2 = 0;                                                      //秒数初始化
    Date = 5;                                                         //星期初始化
}

//万年历显示函数
void calendarShow()
{
    lcd.setCursor(3, 0);
    lcd.print(Y1);
    lcd.print(Y2);
    lcd.print(Y3);
    lcd.print(Y4);
    lcd.print("/");
    lcd.print(M1);
    lcd.print(M2);
    lcd.print("/");
    lcd.print(D1);
    lcd.print(D2);
    //lcd.print("日");
    lcd.setCursor(1, 1);
    lcd.print(H1);
    lcd.print(H2);
    lcd.print(":");
    lcd.print(MI1);
    lcd.print(MI2);
    lcd.print(":");
    lcd.print(S1);
    lcd.print(S2);
    lcd.setCursor(10, 1);
    switch (Date + 1) {
    case 1:lcd.print("Mon"); break;
    case 2:lcd.print("Tue"); break;
    case 3:lcd.print("Wes"); break;
    case 4:lcd.print("Thu"); break;
    case 5:lcd.print("Fri"); break;
    case 6:lcd.print("Sat"); break;
    case 7:lcd.print("Sun"); break;
    default:lcd.print("Error!"); break;
    }
}


void xblink()//定义某一块闪烁的函数
{
    lcd.setCursor(x, y);
    lcd.blink();
}
void xNoblink() {
    lcd.noBlink();
}

//时间流动函数
void tita(int * H1,int * H2,int * MI1,int * MI2,int * S1,int * S2) {

    //***这里有一段代码需要补充 
    *S2 += 1;
    if (*S2 == 10)
    {
        *S2 = 0;
        *S1 += 1;
        if (*S1 == 6)
        {
            *S1 = 0;
            *MI2 += 1;
            if (*MI2 == 10)
            {
                *MI2 = 0;
                *MI1 += 1;
                if (*MI1 == 6)
                {
                    *MI1 = 0;
                    *H2 += 1;
                    if (*H1 == 2 && *H2 == 4)
                    {
                        *H1 = 0;
                        *H2 = 0;
                        date();
                    }
                    if (*H2 == 10)
                    {
                        *H2 = 0;
                        *H1 += 1;
                    }
                }
            }
        }
    }



    if (Alarm_S1 == *S1 && Alarm_S2 == *S2 && Alarm_MI2 == *MI2 && Alarm_MI1 == *MI1 && Alarm_H2 == *H2 && Alarm_H1 == *H1 && Alarm_D2 == D2 && Alarm_D1 == D1 && Alarm_M2 == M2 && Alarm_M1 == M1) {
        //响闹铃
        Serial.print(Alarm_H1);
        Serial.print(Alarm_H2);
        Serial.print(":");
        Serial.print(Alarm_MI1);
        Serial.print(Alarm_MI2);
        Serial.print(":");
        Serial.print(Alarm_S1);
        Serial.print(Alarm_S2);
        buzzer_flag = true;    //启动蜂鸣器
    }
}

//日期流动函数
void date() {
    //***这里有一段代码需要补充 
    Date = (Date + 1) % 7;
    D2 += 1;
    if (D2 == 10) D1 += 1;
    if ((D2 + D1 * 10) > dayOfMonth[M2 + M1 * 10][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)])//如果日期大于月份总天数
    {
        D1 = 0;
        D2 = 0;
        M2 += 1;
        if (M2 == 10) { M2 = 0; M1 += 1; }
        if (M1 == 1 && M2 == 3)//12个月走完了
        {
            M1 = 0;
            M2 = 0;
            Y4 += 1;
            if (Y4 == 10)
            {
                Y4 = 0;
                Y3 += 1;
                if (Y3 == 10)
                {
                    Y3 = 0;
                    Y2 += 1;
                    if (Y2 == 10)
                    {
                        Y2 = 0;
                        Y1 += 1;
                        if (Y1 == 10)//时间轮回
                        {
                            Y1 = 0;
                            Y2 = 0;
                            Y3 = 0;
                            Y4 = 0;
                        }
                    }
                }
            }
        }
    }
    
}
//增加时间数位的函数
void addTime() {
    //***这里有一段代码需要补充 
    switch (modifyIndex+1)
    {
    case 1:
        Y1 = getmol(Y1, 10,0);
        break;
    case 2:
        Y2 = getmol(Y2, 10,0);
        break;
    case 3:
        Y3 = getmol(Y3, 10,0);
        break;
    case 4:
        Y4 = getmol(Y4, 10,0);
        break;
    case 5:
        M2 += 1;
        if (M2 == 10)
        {
            M2 = 0;
            M1 += 1;          
        }
        if (M1 == 1 && M2 == 3) { M1 = 0; M2 = 1; }
        break;
    case 6:
        D2 += 1;
        if (D2 == 10)
        {
            D2 = 0;
            D1 += 1;
        }
        if ((D2 + D1 * 10) > dayOfMonth[M2 + M1 * 10][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]) { D1 = 0; D2 = 1; }

        break;
    case 7:
        H2 += 1;
        
        if (H2 == 10)
        {
            H2 = 0;
            H1 += 1;
        }
        if (H1 == 2 && H2 == 4) { H1 = 0; H2 = 0; }
        
        break;
    case 8:
        MI2 += 1;
        if (MI2 == 10)
        {
            MI2 = 0;
            MI1 += 1;
        }
        if (MI1 == 6) { MI1 = 0; MI2 = 0; }
        break;
    case 9:
        S2 += 1;
        if (S2 == 10)
        {
            S2 = 0;
            S1 += 1;
        }
        if (S1 == 6) { S1 = 0; S2 = 0; }
        break;
    }
    Date = WeekCalc(Y1, Y2, Y3, Y4, M1, M2, D1, D2);
    calendarShow();
    xblink();
}
//减少时间的函数
void minusTime() {
    //***这里有一段代码需要补充 
    //***这里有一段代码需要补充 
    switch (modifyIndex + 1)
    {
    case 1:
        Y1 = getmol(Y1, 10, 1);
        break;
    case 2:
        Y2 = getmol(Y2, 10, 1);
        break;
    case 3:
        Y3 = getmol(Y3, 10, 1);
        break;
    case 4:
        Y4 = getmol(Y4, 10, 1);
        break;
    case 5:
        M2 -= 1;
        if (M2 == -1)
        {
            M2 = 9;
            M1 -= 1;
        }
        if (M1 == 0 && M2 == 0) { M1 = 1; M2 = 2; }
        break;
    case 6:
        D2 -= 1;
        if (D2 == -1)
        {
            D2 = 9;
            D1 -= 1;
        }
        if ((D2 + D1 * 10) == 0)
        {
            D1 = (dayOfMonth[M2 + M1 * 10][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]) / 10; 
            D2 = (dayOfMonth[M2 + M1 * 10][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]) % 10;
        }

        break;
    case 7:
        H2 -= 1;
        if (H1 == 0 && H2 == -1) { H1 = 2; H2 = 3; }
        
        if (H2 == -1)
        {
            H2 = 9;
            H1 -= 1;
        }
        
        break;
    case 8:
        MI2 -= 1;
        if (MI1 == 0 && MI2 == -1) { MI1 = 5; MI2 = 9; }
        if (MI2 == -1)
        {
            MI2 = 9;
            MI1 -= 1;
        }
        
        break;
    case 9:
        S2 -= 1;
        if (S1 == 0 && S2 == -1) { S1 = 5; S2 = 9; }
        if (S2 == -1)
        {
            S2 = 9;
            S1 -= 1;
        }
        
        break;
    }
    Date = WeekCalc(Y1, Y2, Y3, Y4, M1, M2, D1, D2) ;
    calendarShow();
    xblink();
}
//设置闹钟的函数
void setAlarm() {
    //***这里有一段代码需要补充 
    Alarm_M1 = M1; Alarm_M2 = M2;
    Alarm_D1 = D1; Alarm_D2 = D2;
    Alarm_H1 = H1; Alarm_H2 = H2;
    Alarm_MI1 = MI1; Alarm_MI2 = MI2;
    Alarm_S1 = S1; Alarm_S2 = S2;
}
