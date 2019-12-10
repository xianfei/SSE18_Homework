#include <IRremote.h>
int RECV_PIN = 10;
int ledPin = 3;
//LED -digital 3
boolean ledState = LOW;         //ledState用来存储LED的状态
IRrecv irrecv(RECV_PIN);
decode_results results;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(ledPin, OUTPUT);        //设置LED为输出状态

}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFDA05F) {   //如果接受到的是电源键的信号，LED翻转状态
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
    irrecv.resume();
  }
}
