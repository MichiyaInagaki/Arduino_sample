#include "HX711.h"

const int AIRPRESS_1_DAT = 9;
const int AIRPRESS_1_CLK = 8;
const int AIRPRESS_2_DAT = 7;
const int AIRPRESS_2_CLK = 6;

HX711 scale1;
HX711 scale2;

void setup() {
  Serial.begin(9600);
  
  scale1.begin(AIRPRESS_1_DAT, AIRPRESS_1_CLK);
  scale1.set_scale(386.3);
  scale1.tare();
  scale2.begin(AIRPRESS_2_DAT, AIRPRESS_2_CLK);
  scale2.set_scale(386.3);
  scale2.tare();
}

char data[100];

void loop() {
  
  Serial.println("");
  if (scale1.is_ready()) {
    long reading1 = scale1.get_units();
    //sprintf(data, "%d", reading1);
    if(reading1==0){
      Serial.print(1);    //0で割り算できないのを防ぐ
    }
    else{
      Serial.print(reading1);
    }
  } 
  Serial.print("\t");
  if (scale2.is_ready()) {
    long reading2 = scale2.get_units();
    //sprintf(data, "%d",  reading2);
    if(reading2==0){
      Serial.print(1);    //0で割り算できないのを防ぐ
    }
    else{
      Serial.print(reading2);
    }
  } 
  Serial.print("\n");
  
  delay(100);
}
