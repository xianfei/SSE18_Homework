
// 传邮万里  完整版  added by xianfei wang

#include "Volume.h" // Include the Volume library
Volume vol;
//歌曲
int Eulogyofjoytune[] =                //根据简谱列出各频率
{
  350, 350, 393, 441,
  441, 393, 350, 330,
  294, 294, 330, 350,
  350, 330, 330,
  350, 350, 393, 441,
  441, 393, 350, 330,
  294, 294, 330, 350,
  330, 294, 294,
  330, 330, 350, 294,
  330, 350, 393, 350, 294,
  330, 350, 393, 350, 330,
  294, 330, 221, -1,
  350, 350, 393, 441,
  441, 393, 350, 393, 330,
  294, 294, 330, 350,
  330, 294, 294
};
int lstune[] = {
  262, 262, 393, 393,
  441, 441, 393,
  350, 350, 330, 330,
  294, 294, 262,
  393, 393, 350, 350,
  330, 330, 294,
  393, 393, 350, 350,
  330, 330, 294,
  262, 262, 393, 393,
  441, 441, 393,
  350, 350, 330, 330,
  294, 294, 262
};

//自定义一首歌的频率
int tune[] = {
  294, 294, 350,
  294, 294, 350,
  495, 495, 495, 441, 495,
  441, 294, 350,
  589, 495, 495, 441, 495,
  441, 294, 330,
  556, 556, 441, 350, 441,

};

//节拍
float Eulogyofjoybeat[] =                  //根据简谱列出各节拍
{
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
  1, 1, 1, 1,
  1, 0.5, 0.5, 1, 1,
  1, 0.5, 0.5, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 0.5, 0.5,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
};
float lsbeat[] = {
  1, 1, 1, 1,
  1, 1, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1 + 1
};
//自定义一首歌的节奏
float beat[] = {
  1, 1, 1 + 1,
  0.5, 1, 1,
  1, 1, 0.5, 0.5,
  0.5, 1, 1,
  0.5, 0.5, 0.5, 0.5, 1 + 1,
  0.5, 1, 1,
  1 + 1 + 0.5, 0.5, 1, 1 + 1 + 1 + 1
};

//设置接口
int buzzerpin = 5;
int ledpin = 3;

void setup() {
  pinMode(buzzerpin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
  vol.begin();
}
//播放歌曲的函数
void start(int len,int buzzpin,int lepin,int *tune,float *beat){
  for(int x=0;x<len;x++)
  {
    vol.tone(tune[x],55);
    digitalWrite(lepin, HIGH); 
    vol.fadeOut(100*beat[x]);//与前一代码不同之处，这里将原来的500分为了400和100，分别控制led的开与关，对于蜂鸣器来说依然是500.
    digitalWrite(lepin, LOW);
    vol.fadeOut(100*beat[x]);//与前一代码不同之处，这里将原来的500分为了400和100，分别控制led的开与关，对于蜂鸣器来说依然是500.
    
  }
}


String select;
void loop() {
  
  while (Serial.available() > 0) {
    select += char(Serial.read());
    delay(2);
  } int len;

  if (select != "") {
    Serial.println(select);
    if (select == "Huluwa") {
      Serial.println("Next,we will play the Huluwa");
      len = sizeof(tune) / sizeof(beat[0]);
      start(len, buzzerpin, ledpin, tune, beat);
    } else if (select == "Ode to Jo") {
      Serial.println("Next, we will play the Ode to Jo");
      len = sizeof(Eulogyofjoytune) / sizeof(Eulogyofjoytune[0]);
      start(len, buzzerpin, ledpin, Eulogyofjoytune, Eulogyofjoybeat);
    } else if (select == "little star") {
      Serial.println("Next, we will play the little star");
      len = sizeof(lstune) / sizeof(lstune[0]);
      start(len, buzzerpin, ledpin, lstune, lsbeat);
    } else {
      Serial.println("Sorry, there is no such song in the music library.");
    }
  }
}
