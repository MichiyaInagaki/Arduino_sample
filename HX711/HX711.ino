#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_1_DAT = 9;
const int LOADCELL_1_CLK = 8;
const int LOADCELL_2_DAT = 7;
const int LOADCELL_2_CLK = 6;
//const int LOADCELL_3_DAT = 5;
//const int LOADCELL_3_CLK = 4;

HX711 scale1;
HX711 scale2;
// HX711 scale3;

void setup() {
  Serial.begin(9600);
  
  scale1.begin(LOADCELL_1_DAT, LOADCELL_1_CLK);
  scale1.set_scale(386.3);
  scale1.tare();
  scale2.begin(LOADCELL_2_DAT, LOADCELL_2_CLK);
  scale2.set_scale(386.3);
  scale2.tare();
/*
  scale3.begin(LOADCELL_3_DAT, LOADCELL_3_CLK);
  scale3.set_scale(386.3);
  scale3.tare();
*/
}

char data[100];

void loop() {
  if (scale1.is_ready()) {
    long reading1 = scale1.get_units();
    sprintf(data, "A:%d\n", reading1);
    Serial.print(data);
  } 
  if (scale2.is_ready()) {
    long reading2 = scale2.get_units();
    sprintf(data, "B:%d \n",  reading2);
    Serial.print(data);
  } 
/*
  if (scale3.is_ready()) {
    long reading3 = scale3.get_units();
    sprintf(data, "C:%d\n",  reading3);
    Serial.print(data);
  }
*/ 
  delay(100);
}
