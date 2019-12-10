#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x20,16,2);//设置LCD的地址，2行，每行16字符
dht11 DHT;
#define DHT11_PIN 4


void setup() {
  // put your setup code here, to run once:
  lcd.init();            // LCD初始化设置
  lcd.backlight();      // 打开 LCD背光
  Serial.begin(9600);  // 设置串口波特率9600
  //串口输出”Type, status, Humidity(%), Temperature(C)”
  Serial.println("Type,\tstatus,\tHumidity(%),\tTemperature(C)");
  lcd.print("Humidity(%): ");   //LCD屏显示” Humidity(%):”
  lcd.setCursor(0, 1);     //光标移到第2行，第一个字符
  lcd.print("Temp(C): ");  //LCD屏显示”Temp(C):”
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk;  //chk用于存储DHT11传感器的数据
  Serial.print("DHT11, \t"); 
//读取 DHT11传感器的数据
  chk = DHT.read(DHT11_PIN);   
  switch (chk){ 
    case DHTLIB_OK: 
        Serial.print("OK,\t"); 
         break; 
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.print("Checksum error,\t");  
        break; 
    case DHTLIB_ERROR_TIMEOUT:
           Serial.print("Time out error,\t");  
           break; 
    default:
            Serial.print("Unknown error,\t");  
            break; 
  }
  //串口显示温湿度值
  Serial.print(DHT.humidity,1);   
  Serial.print(",\t"); 
  Serial.println(DHT.temperature,1); 
  //LCD显示温湿度值
  lcd.setCursor(12, 0); 
  lcd.print(DHT.humidity,1); 
  lcd.setCursor(8, 1); 
  lcd.print(DHT.temperature,1); 
  delay(1000); 
}
