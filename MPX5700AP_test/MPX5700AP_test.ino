//空気圧センサ
//アナログピン番号
const int PIN_ANALOG_INPUT_0 = 0;   
const int PIN_ANALOG_INPUT_1 = 1;

void setup() {
  Serial.begin( 9600 );
}

void loop() {
  int i_pin0 = analogRead( PIN_ANALOG_INPUT_0 );
  int i_pin1 = analogRead( PIN_ANALOG_INPUT_1 );
  float f_pin0 = i_pin0 * 5.0 / 1023.0;
  float f_pin1 = i_pin1 * 5.0 / 1023.0;
  Serial.print( f_pin0 );
  Serial.print("\t");
  Serial.print( f_pin1 ); 
  Serial.print("\n");  
  delay( 100 ); 
}
