
/*功能说明：
   电源键：返回主界面
   1键：修改时间
   2键：设定闹钟
   3键：修改日期
   4键：取消闹钟
   5键：切换24小时制
   6键：显示温度
   7键：切换背光开关
修改时间日期及设置闹钟使用0-9键输入
显示alamr则表示闹钟已设定
*/

//在这里自定义遥控按键
#define edittimeKey 1
#define setAlarmKey 2
#define editdayKey 3
#define cancelAlarmKey 4
#define use24hKey 5
#define showtempKey 6
#define backlightKey 7

//在这里设置端口信息
#define DHT11_PIN 4  //温度计模块接口
#define buzzpin 5  //蜂鸣器接收端口
#define RECV_PIN 10 //红外接收端口

//在这里设定初始化的 时 分 秒 年 月 日 星期
static short h = 10, m = 16, s = 30, y = 2018, mon = 11, day = 23, xq = 5;

//在这里自定义是否使用24h制、显示温度
bool use24h=1,showtemp=0;

//在这里自定义启动画面显示的信息
#define bootinf "by xianfei"

//以下是代码部分
#include "dht11.h"
dht11 DHT;
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
IRrecv irrecv(RECV_PIN);
decode_results results;
LiquidCrystal_I2C lcd(0x20, 16, 2); //设置LCD的地址，2行，每行16字符
static char t[9], d[12];
static short edittime = 0, editdate = 0, editalarm = 0, curs,backLight=1;
static short ah = 25, am = 0;
#define editmode (edittime || editdate || editalarm)

void setup()
{
  lcd.init();         // LCD初始化设置
  lcd.backlight();    // 打开 LCD背光
  //Serial.begin(9600); // 设置串口波特率9600
  irrecv.enableIRIn();
  pinMode(buzzpin, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Booting...");
  lcd.setCursor(0, 1);
  lcd.print(bootinf);
  delay(1000);
  lcd.clear();
}

void loop()
{
  for (int i = 0; i < 950; i++)
  {
    recv(); //接受遥控信号
    delay(1);
  }
  if (!edittime)
    gettime(); //获取时间及时间流动
  if (!(editmode || (ah == h && am == m)))
    output(); //如果不在编辑模式 将输出时间日期
  if (ah == h && am == m)
    alarmrun(); //闹钟响铃部分
}

void recv()
{
      if (irrecv.decode(&results))
    {
      //Serial.println(results.value, HEX);
      if (results.value == 0xFD30CF)
      {
        remote(0);
      }
      if (results.value == 0xFD08F7)
      {
        remote(1);
      }
      if (results.value == 0xFD8877)
      {
        remote(2);
      }
      if (results.value == 0xFD48B7)
      {
        remote(3);
      }
      if (results.value == 0xFD28D7)
      {
        remote(4);
      }
      if (results.value == 0xFDA857)
      {
        remote(5);
      }
      if (results.value == 0xFD6897)
      {
        remote(6);
      }
      if (results.value == 0xFD18E7)
      {
        remote(7);
      }
      if (results.value == 0xFD9867)
      {
        remote(8);
      }
      if (results.value == 0xFD58A7)
      {
        remote(9);
      }
      if (results.value == 0xFD00FF)
      {
        edittime = 0;
        editdate = 0;
        editalarm = 0;
        lcd.clear();
        lcd.noBlink();
        ah = 25, am = 0;
        digitalWrite(buzzpin, LOW);
      }
      irrecv.resume();
    }
}

void output()
{
  //显示闹钟标识及时间
  if ((ah == 25)&&use24h)
    lcd.setCursor(4, 1);
  if ((ah == 25)&&!use24h)
    lcd.setCursor(3, 1);
  if ((ah != 25))
    lcd.setCursor(1, 1);
  lcd.print(t);
  if ((ah != 25)&&use24h)
  lcd.print(" alarm");  
  if ((ah != 25)&&!use24h){
    if(h>12)lcd.print("PM"); 
    else lcd.print("AM");
    lcd.print(" alm");  
  }
  if ((ah == 25)&&!use24h)
    {
      if(h>12)lcd.print("PM"); 
      else lcd.print("AM");
    }
  
  //显示日期部分
  lcd.setCursor(1, 0);
  if(showtemp){

  lcd.print(&d[1]);
  lcd.print(" ");
  }
  else{
    lcd.print(y);
  lcd.print(d);
  lcd.print(" ");
  }
  //显示星期部分
  switch (xq)
  {
  case 1:
    lcd.print("Mon");
    break;
  case 2:
    lcd.print("Tue");
    break;
  case 3:
    lcd.print("Wes");
    break;
  case 4:
    lcd.print("Sat");
    break;
  case 5:
    lcd.print("Fri");
    break;
  case 6:
    lcd.print("Sat");
    break;
  case 7:
    lcd.print("Sun");
    break;
  default:
    lcd.print("Err");
  }
  if(showtemp){
    DHT.read(DHT11_PIN);
    lcd.print(" ");
    lcd.print(DHT.temperature,1);
  
  }
}

void alarmrun()
{
  static bool bee;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm is beeing...");
  lcd.setCursor(0, 1);
  lcd.print("Stop after ");
  lcd.print(60 - s);
  lcd.print("s");
  if (bee)
    digitalWrite(buzzpin, HIGH);
  if (!bee)
    digitalWrite(buzzpin, LOW);
  bee = !bee;
  if (s == 59)
    lcd.clear();
}

int remote(int recv)
{
  if (recv == backlightKey && !editmode){
    backLight=!backLight;
    if(backLight)lcd.backlight(); 
    else lcd.noBacklight();
    return 0;
  }
  if (recv == showtempKey && !editmode){
    showtemp=!showtemp;
    lcd.clear();
    return 0;
  }
  if (recv == use24hKey && !editmode){
    use24h=!use24h;
    lcd.clear();
    return 0;
  }
  if (recv == cancelAlarmKey && !editmode)
  {
    ah = 25;
    digitalWrite(buzzpin, LOW);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Alarm canceled");
    s++;
    delay(960);
    return 0;
  }
  if (recv == editdayKey && !editmode)
  {
    editdate = 1;
    curs = 2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input day:");
    lcd.setCursor(6, 1);
    lcd.print("-");
    lcd.setCursor(9, 1);
    lcd.print("-");
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
    return 0;
  }
  if (recv == edittimeKey && !editmode)
  {
    edittime = 1;
    curs = 3;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input time:");
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(8, 1);
    lcd.print(":");
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
    return 0;
  }
  if (recv == setAlarmKey && !editmode)
  {
    editalarm = 1;
    curs = 3;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input alarm time:");
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(8, 1);
    lcd.print(":00");
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
    return 0;
  }
  if (editalarm)
  {
    lcd.setCursor(curs, 1);
    lcd.print(recv);
    switch (curs)
    {
    case 3:
      ah = recv * 10;
      break;
    case 4:
      ah = ah + recv;
      break;
    case 6:
      am = recv * 10;
      break;
    case 7:
      am = am + recv;
      break;
    }
    if (curs == 7)
    {
      lcd.clear();
      editalarm = 0;
      lcd.noBlink();
      return 0;
    }
    if (curs == 4)
    {
      lcd.setCursor(curs + 1, 1);
      lcd.print(":");
      curs++;
    }
    curs++;
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
  }
  if (edittime)
  {
    lcd.setCursor(curs, 1);
    lcd.print(recv);
    switch (curs)
    {
    case 3:
      h = recv * 10;
      break;
    case 4:
      h = h + recv;
      break;
    case 6:
      m = recv * 10;
      break;
    case 7:
      m = m + recv;
      break;
    case 9:
      s = recv * 10;
      break;
    case 10:
      s = s + recv;
      break;
    }
    if (curs == 10)
    {
      lcd.clear();
      edittime = 0;
      lcd.noBlink();
      return 0;
    }
    if (curs == 4 || curs == 7)
    {
      lcd.setCursor(curs + 1, 1);
      lcd.print(":");
      curs++;
    }
    curs++;
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
  }
  if (editdate)
  {
    lcd.setCursor(curs, 1);
    lcd.print(recv);
    switch (curs)
    {
    case 2:
      y = recv * 1000;
      break;
    case 3:
      y = recv * 100 + y;
      break;
    case 4:
      y = recv * 10 + y;
      break;
    case 5:
      y = recv + y;
      break;
    case 7:
      mon = recv * 10;
      break;
    case 8:
      mon = recv + mon;
      break;
    case 10:
      day = 10 * recv;
      break;
    case 11:
      day = day + recv;
      break;
    }
    if (curs == 11)
    {
      lcd.setCursor(0, 0);
      lcd.print("Input week:(0-7)");
    }

    if (curs == 12)
    {
      xq = recv;
      lcd.clear();
      editdate = 0;
      lcd.noBlink();
      return 0;
    }
    if (curs == 5 || curs == 8)
    {
      lcd.setCursor(curs + 1, 1);
      lcd.print("-");
      curs++;
    }
    curs++;
    lcd.setCursor(curs, 1);
    lcd.blink();
    delay(50);
  }
}

void gettime()
{
  s++;
  if (s > 59) 
  {
    s = 0;
    m++;
  }
  if (m > 59) 
  {
    m = 0;
    h++;
  }
  if (h > 23)
  {
    h = 0;
    day++;
    xq++;
  }
  if (xq > 7)
  {
    xq = 1;
  }
  if (s < 10)
  {
    t[7] = '0' + s;
    t[6] = '0';
  }
  else
  {
    t[7] = '0' + s % 10;
    t[6] = '0' + s / 10;
  }
  if (m < 10)
  {
    t[4] = '0' + m;
    t[3] = '0';
  }
  else
  {
    t[4] = '0' + m % 10;
    t[3] = '0' + m / 10;
  }
  if((!use24h)&&(h>12)){
    if (h-12 < 10)
  {
    t[1] = '0' + h-12;
    t[0] = '0';
  }
  else
  {
    t[1] = '0' + h-12 % 10;
    t[0] = '0' + h-12 / 10;
  }
  
  }else{
      if (h < 10)
  {
    t[1] = '0' + h;
    t[0] = '0';
  }
  else
  {
    t[1] = '0' + h % 10;
    t[0] = '0' + h / 10;
  }
  }
  t[2] = ':';
  t[5] = ':';
  short daymax[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (y / 100 != 0 && y % 4 == 0 || y / 400 == 0)
  {
    daymax[2] = 29;
  }
  else
  {
    daymax[2] = 28;
  }
  if (day > daymax[mon])
  {
    day = 1;
    mon++;
  }
  if (mon > 12)
  {
    mon = 1;
    y++;
  }
  if (day < 10)
  {
    d[5] = '0' + day;
    d[4] = '0';
  }
  else
  {
    d[5] = '0' + day % 10;
    d[4] = '0' + day / 10;
  }

  if (mon < 10)
  {
    d[2] = '0' + mon;
    d[1] = '0';
  }
  else
  {
    d[2] = '0' + mon % 10;
    d[1] = '0' + mon / 10;
  }
  d[0] = '-';
  d[3] = '-';
}
