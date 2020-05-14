//ロードセル
//アナログピン番号
const int PIN_ANALOG_INPUT_0 = 0;   
const int PIN_ANALOG_INPUT_1 = 1;
const int PIN_ANALOG_INPUT_2 = 2;   
const int PIN_ANALOG_INPUT_3 = 3;

void setup() {
  Serial.begin( 38400 );
}

void loop() {
  int i_pin0 = analogRead( PIN_ANALOG_INPUT_0 );
  int i_pin1 = analogRead( PIN_ANALOG_INPUT_1 );
  int i_pin2 = analogRead( PIN_ANALOG_INPUT_2 );
  int i_pin3 = analogRead( PIN_ANALOG_INPUT_3 );  
  float f_pin0 = i_pin0 * 5.0 / 1023.0;
  float f_pin1 = i_pin1 * 5.0 / 1023.0;
  float f_pin2 = i_pin2 * 5.0 / 1023.0;
  float f_pin3 = i_pin3 * 5.0 / 1023.0;
  //Serial.print( "pin0: " );
  Serial.print( f_pin0 );
  Serial.print("\t");
  //Serial.print( "pin1: " );
  Serial.print( f_pin1 );
  Serial.print("\t");
  Serial.print( f_pin2 );
  Serial.print("\t");
  Serial.print( f_pin3 );    
  Serial.print("\n");  
  delay( 100 ); 
}
