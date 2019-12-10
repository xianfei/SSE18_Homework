#include <IRremote.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

int RECV_PIN = 10;                                               //定义红外接收的数字引脚口为10号口
int ALARM_PIN = 4;                                               //定义蜂鸣器的接口为4
IRrecv irrecv(RECV_PIN);
decode_results results;                                        //定义红外接收装置的接收结果变量

/*定义修改位的在液晶屏上的x坐标，
  分别对应Y1,Y2,Y3,Y4,M1,M2,D1,D2,
  H1,H2,MI1,MI2,S1,S2，
  第二行的加上了一个偏移量12
*/
int pos[] = {3, 4, 5, 6, 8, 9, 11, 12,
             13, 14, 16, 17, 19, 20
            };

int modifyIndex;

boolean light_flag;                                              //定义lcd屏亮暗标志，true表示亮屏，false表示暗屏
boolean modify_flag;                                             //定义修改时间模式标志位，true表示修改时间模式，false表示非修改时间模式
boolean alarm_flag;                                              //定义设置闹铃模式标志位，true表示设置闹钟模式，false表示非设置闹钟模式
boolean buzzer_flag;


//定义全局时间变量--年 月 日 时 分 秒
int Y1, Y2, Y3, Y4;                                              //定义年份的四位，从高到低
int M1, M2;                                                      //定义月份的两位，从高到低
int D1, D2;                                                      //定义日期的两位，从高到低
int H1, H2;                                                      //定义小时的两位，从高到低
int MI1, MI2;                                                    //定义分钟的两位，从高到低
int S1, S2;                                                      //定义秒数的两位，从高到低
int Date;                                                        //定义星期


//定义全局闹铃时间变量--月 日 时 分
int Alarm_M1, Alarm_M2;                                                      //定义月份的两位，从高到低
int Alarm_D1, Alarm_D2;                                                      //定义日期的两位，从高到低
int Alarm_H1, Alarm_H2;                                                      //定义小时的两位，从高到低
int Alarm_MI1, Alarm_MI2;                                                    //定义分钟的两位，从高到低
int Alarm_S1, Alarm_S2;                                                      //定义秒数的两位，从高到低


//定义临时变量存储时间
int temp_Y1, temp_Y2, temp_Y3, temp_Y4;                                              //定义年份的四位，从高到低
int temp_M1, temp_M2;                                                      //定义月份的两位，从高到低
int temp_D1, temp_D2;                                                      //定义日期的两位，从高到低
int temp_H1, temp_H2;                                                      //定义小时的两位，从高到低
int temp_MI1, temp_MI2;                                                    //定义分钟的两位，从高到低
int temp_Date;                                                        //定义星期
int temp_S1, temp_S2;                                                 //定义秒数的两位，从高到低


//定义判断闰年的函数
#define ISYEARP(x) x/100!=0&&x%4==0||x/400==0?1:0
//定义每个月的天数
int dayOfMonth[13][2] = {
  0, 0,
  31, 31,
  28, 29,
  31, 31,
  30, 30,
  31, 31,
  30, 30,
  31, 31,
  31, 31,
  30, 30,
  31, 31,
  30, 30,
  31, 31,
};

int x, y;                                                       //定义修改液晶屏的时间数位的横纵坐标




//功能函数定义

void addTime();                                                 //定义增加时间的函数，执行结果会使当前光标处的时间数位加一
void minusTime();                                               //定义减少时间的函数，执行结果会使当前光标处的时间数位减一
void setAlarm();                                                //定义设置闹钟的函数
void tita();                                                    //定义时间流动函数
void date();                                                    //定义日期的流动函数
void calendarInit();                                            //定义万年历初始化函数
void calendarShow();                                            //定义万年历的显示函数
void xblink();                                                  //定义某一块闪烁的函数
void xNoblink();                                                //定义某一块不闪烁的函数

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
    if (results.value == 0xFD00FF) {   //如果接受到的是电源键的信号，万年历亮屏或者息屏

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
    else if (results.value == 0xFD08F7 ) {                    //如果接受到的是1信号，则进入修改时间模式或非修改时间模式
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
    else if (results.value == 0xFD8877)                       //如果接受的是2信号，则进入取消闹铃，设置闹钟模式，或定好闹钟模式
    {
      if (alarm_flag == true)                                   //之前是设置闹钟模式，现在要进入设置好闹钟，需要保存闹铃信息，并退出修改时间模式和闹钟模式
      {
        //保存闹钟变量
        xNoblink();
        modify_flag = false;
        alarm_flag = !alarm_flag;
        setAlarm();
        //恢复时间
        Y1 = temp_Y1, Y2 = temp_Y2, Y3 = temp_Y3, Y4 = temp_Y4, M1 = temp_M1, M2 = temp_M2, D1 = temp_D1, D2 = temp_D2, H1 = temp_H1, H2 = temp_H2, MI1 = temp_MI1, MI2 = temp_MI2, S1 = temp_S1, S2 = temp_S2;
      }
      else {                                                    //之前并不是设置闹钟模式，现在要进入设置闹钟模式
        temp_Y1 = Y1, temp_Y2 = Y2, temp_Y3 = Y3, temp_Y4 = Y4, temp_M1 = M1, temp_M2 = M2, temp_D1 = D1, temp_D2 = D2, temp_H1 = H1, temp_H2 = H2, temp_MI1 = MI1, temp_MI2 = MI2, temp_S1 = S1, temp_S2 = S2; //保存设置闹钟前的当前时间
        modify_flag = true;
        buzzer_flag = false;
        //modifyIndex=8;
        x = 1;
        y = 1;                                                  //设置好光标的坐标
        xblink();
        modifyIndex = 8;
        alarm_flag = true;
      }
    }
    else if (results.value == 0xFD20DF)                       //如果接收到的是左快进的信号
    {
      if (modify_flag) {
        xNoblink();
        modifyIndex = (modifyIndex + 13) % 14;
        x = pos[modifyIndex];
        if (x > 12) {                                       //如果横坐标到了逻辑上的第二行，则要将其减去偏移量12，并使纵坐标为1
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
        modifyIndex = (modifyIndex + 1) % 14;
        x = pos[modifyIndex];                        //如果横坐标到了逻辑上的第二行，则要将其减去偏移量12，并使纵坐标为1
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
    else if (results.value == 0xFD807F)                          //如果接受到的是vol+信号，则调整当前数位的值加一，值可循环
    {
      if (modify_flag) {
        addTime();
      }
    }
    else if (results.value == 0xFD906F)                          //如果接受到的是vol-信号，则调整当前数位的值减一，值可循环
    {
      if (modify_flag) {
        minusTime();
      }
    }
    irrecv.resume();
  }
  if (modify_flag == false && alarm_flag == false)              //如果正处于修改时间模式或者 定闹钟模式，则暂缓时间的刷新显示
  {
    calendarShow();                  //时间暂停刷新
    tita();                           //不管什么模式，时间都一样地流动
  }

  delay(1000);

  if (buzzer_flag) {
    digitalWrite(ALARM_PIN, HIGH);
  }
  else {
    digitalWrite(ALARM_PIN, LOW);
  }
}

//万年历初始化函数，加串口通信读取电脑当前时间
void calendarInit()
{
  Y1 = 2, Y2 = 0, Y3 = 1, Y4 = 8;                                 //年份初始化
  M1 = 0, M2 = 9;                                                 //月份初始化
  D1 = 1, D2 = 8;                                                 //日期初始化
  H1 = 1, H2 = 4;                                                 //小时初始化
  MI1 = 2, MI2 = 3;                                                 //分钟初始化
  S1 = 3, S2 = 0;                                                 //秒数初始化
  Date = 2;                                                       //星期初始化
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
    case 1: lcd.print("Mon"); break;
    case 2: lcd.print("Tue"); break;
    case 3: lcd.print("Wes"); break;
    case 4: lcd.print("Sat"); break;
    case 5: lcd.print("Fri"); break;
    case 6: lcd.print("Sat"); break;
    case 7: lcd.print("Sun"); break;
    default: lcd.print("Error!"); break;
  }
}

//时间流动函数
void tita() {
  S2 = S2 + 1;
  if (S2 == 10)
  {
    S2 = 0;
    S1 = S1 + 1;
    if (S1 == 6)
    {
      S1 = 0;
      MI2 = MI2 + 1;
      if (MI2 == 10)
      {
        MI2 = 0;
        MI1 = MI1 + 1;
        if (MI1 == 6)
        {
          MI1 = 0;
          H2 = H2 + 1;
          if (H1 == 2 && H2 == 4)
          {
            H1 = 0;
            H2 = 0;
            date();
          }
          if (H2 == 10)
          {
            H2 = 0;
            H1 = H1 + 1;

          }
        }
      }
    }
  }
  if (Alarm_S1 == S1 && Alarm_S2 == S2 && Alarm_MI2 == MI2 && Alarm_MI1 == MI1 && Alarm_H2 == H2 && Alarm_H1 == H1 && Alarm_D2 == D2 && Alarm_D1 == D1 && Alarm_M2 == M2 && Alarm_M1 == M1 ) {
    //响闹铃
    Serial.print(Alarm_H1);
    Serial.print(Alarm_H2);
    Serial.print(":");
    Serial.print(Alarm_MI1);
    Serial.print(Alarm_MI2);
    Serial.print(":");
    Serial.print(Alarm_S1);
    Serial.print(Alarm_S2);
    buzzer_flag = true;  //启动蜂鸣器
  }
}


//日期流动函数
void date() {
  Date = (Date + 1) % 7;
  D2 = D2 + 1;
  if ( D2 + D1 * 10 > (dayOfMonth[M1 * 10 + M2][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]))
  {
    D1 = 0;
    D2 = 1;
    M2 = M2 + 1;
    if (M1 == 1 && M2 == 3)
    {
      M1 = 0;
      M2 = 1;
      Y4 = Y4 + 1;
      if (Y4 == 10)
      {
        Y4 = 0;
        Y3 = Y3 + 1;
        if (Y3 == 10)
        {
          Y3 = 0;
          Y2 = Y2 + 1;
          if (Y2 == 10)
          {
            Y2 = 0;
            Y1 = Y1 + 1;
            if (Y1 == 10)
            {
              Y1 = 0;
            }
          }
        }
      }
    }
    if (M2 == 10)
    {
      M2 = 0;
      M1 = M1 + 1;
    }
  }
  if (D2 == 10) {
    D2 = 0;
    D1 = D1 + 1;
  }
}
void xblink() {
  lcd.setCursor(x, y);
  lcd.blink();
}
void xNoblink() {
  lcd.noBlink();
}
//增加时间数位的函数
void addTime()
{
  int days;
  int a;
  int b;

  //修改时间
  if (y == 0) {                  //年月日的修改
    if (x == 8)                  //M1的修改
    {
      if (M2 < 3) {              //这种情况下M1可以等于0或1
        M1 = (M1 + 1) % 2;
      }
      else {                      //当M2>=3是M1只能等于0，因为不存在13,14,15等等的月份，只有十二个月
        M1 = 0;
      }
      lcd.print(M1);
    }
    else if (x == 9)              //M2的修改
    {
      if (M1 == 0) {
        M2 = (M2 + 1);
        if (M2 == 10) {
          M2 = 1;
        }
      }
      else {
        M2 = (M2 + 1) % 3;
      }
      lcd.print(M2);
    }
    else if (x == 11) {           //D1的修改
      days = dayOfMonth[M1 * 10 + M2][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]; //先根据年份，月份获取该月的总天数
      a = days / 10;                  //获取总天数的整数部分
      b = days % 10;                  //获取总天数的余数部分
      if (D2 <= b) {
        D1 = (D1 + 1) % (a + 1);
      }
      else {
        D1 = (D1 + 1) % a;
      }
      lcd.print(D1);
    }
    else if (x == 12) {         //D2的修改
      days = dayOfMonth[M1 * 10 + M2][ISYEARP(Y1 * 1000 + Y2 * 100 + Y3 * 10 + Y4)]; //先根据年份，月份获取该月的总天数
      a = days / 10;                  //获取总天数的整数部分
      b = days % 10;                  //获取总天数的余数部分
      if (D1 == a) {
        if (b == 0) {
          D2 = 0;
        }
        else {
          D2 = (D2 + 1) % (b + 1);
        }
      }
      else if (D1 == 0) {
        D2 = D2 + 1;
        if (D2 == 10) {
          D2 = 1;
        }
      }
      else {
        D2 = (D2 + 1) % 10;
      }
      lcd.print(D2);
    }
    else if (x == 3) {                       //其他数位上的修改，只用遵守简单的十进制逻辑即可
      Y1 = (Y1 + 1) % 10;
      lcd.print(Y1);
    }
    else if (x == 4) {
      Y2 = (Y2 + 1) % 10;
      lcd.print(Y2);
    }
    else if (x == 5) {
      Y3 = (Y3 + 1) % 10;
      lcd.print(Y3);
    }
    else if (x == 6) {
      Y4 = (Y4 + 1);
      if (Y4 == 10) {
        Y4 = 1;
      }
      lcd.print(Y4);
    }
  }
  else {                        //时分秒的修改
    if (x == 1) {               //H1的修改
      if (H2 <= 3 && H2 != 0) {
        H1 = (H1 + 1) % 3;
      }
      else if (H2 == 0) {
        H1 = H1 + 1;
        if (H1 == 3) {
          H1 = 1;
        }
      }
      else {
        H1 = (H1 + 1) % 2;
      }
      lcd.print(H1);
    }
    else if (x == 2) {
      if (H1 == 2) {
        H2 = (H2 + 1) % 4;
      }
      else {
        H2 = (H2 + 1) % 10;
      }
      lcd.print(H2);
    }
    else if (x == 4) {
      MI1 = (MI1 + 1) % 6;
      lcd.print(MI1);
    }
    else if (x == 5) {
      MI2 = (MI2 + 1) % 10;
      lcd.print(MI2);
    }
    else if (x == 7) {
      S1 = (S1 + 1) % 6;
      lcd.print(S1);
    }
    else {
      S2 = (S2 + 1) % 10;
      lcd.print(S2);
    }
  }
  //calendarShow();
  lcd.setCursor(x, y);

}
//减少时间的函数
void minusTime() {

}
//设置闹钟的函数
void setAlarm() {
  Alarm_M1 = M1;
  Alarm_M2 = M2;
  Alarm_D1 = D1;
  Alarm_D2 = D2;
  Alarm_H1 = H1;
  Alarm_H2 = H2;
  Alarm_MI1 = MI1;
  Alarm_MI2 = MI2;
  Alarm_S1 = S1;
  Alarm_S2 = S2;
}
