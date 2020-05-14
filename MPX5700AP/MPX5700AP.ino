//空気圧センサ
//アナログピン番号
const int PIN_ANALOG_INPUT_0 = 0;   
const int PIN_ANALOG_INPUT_1 = 1;
//
int rawValue_0; // A/D readings
int rawValue_1; // A/D readings
int offset = 410; // zero pressure adjust
int fullScale = 9630; // max pressure (span) adjust
float pressure_0; // final pressure
float pressure_1; // final pressure
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  rawValue_0 = 0;
  rawValue_1 = 0;
  for (int x = 0; x < 10; x++){
    rawValue_0 = rawValue_0 + analogRead(PIN_ANALOG_INPUT_0);
    rawValue_1 = rawValue_1 + analogRead(PIN_ANALOG_INPUT_1);
  }
  pressure_0 = (rawValue_0 - offset) * 700.0 / (fullScale - offset); // pressure conversion
  pressure_1 = (rawValue_1 - offset) * 700.0 / (fullScale - offset); // pressure conversion
  
  //Serial.print("Raw A/D is  ");
  //Serial.print(rawValue_0);
  //Serial.print("   Pressure is  ");
  Serial.print(pressure_0, 1); // one decimal places
  //Serial.print("  kPa");
  Serial.print("\t");
  //Serial.print("Raw A/D is  ");
  //Serial.print(rawValue_1);
  //Serial.print("   Pressure is  ");
  Serial.print(pressure_1, 1); // one decimal places
  //Serial.print("  kPa");
  Serial.print("\n");
  delay(100);
}
