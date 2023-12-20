
#include <SoftwareSerial.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

volatile int flag;
volatile int times;
SoftwareSerial mySerial(10,11);
DFRobotDFPlayerMini myPlayer;

void setup(){
  flag = 0;
  times = 0;
  mySerial.begin(9600);
  myPlayer.begin(mySerial);
  myPlayer.volume(20);
  myPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop(){
  while (digitalRead(3) == HIGH) {
    digitalWrite(13,HIGH);
    if (flag == 0) {
      myPlayer.enableDAC();
      myPlayer.play(1);
      flag = 1;

    }
    if (digitalRead(2) == HIGH) {
      times++;
      if (times > 0 && times <= 10) {
        myPlayer.play((random(2, 5)));
        delay(1000);

      } else if (times >= 11 && times <= 20) {
        myPlayer.play((random(5, 8)));
        delay(1000);
      } else if (times >= 21 && times <= 40) {
        myPlayer.play((random(8, 14)));
        delay(1000);
      } else if (times >= 41) {
        myPlayer.play((random(14, 18)));
        delay(1000);
      }

    }
  }
  if (flag == 1) {
    myPlayer.disableDAC();
    times = 0;
    flag = 0;
    delay(5000);

  }

}