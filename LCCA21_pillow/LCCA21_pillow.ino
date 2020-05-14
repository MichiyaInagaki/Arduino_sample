//ロードセル枕
//アナログピン番号
const int PIN_ANALOG_INPUT_0 = 0;   
const int PIN_ANALOG_INPUT_1 = 1;
// 初期化用
float initial_pin0 = 0.0f;
float initial_pin1 = 0.0f;

void setup() {
  Serial.begin( 9600 );
}

void loop() {
  int i_pin0 = analogRead( PIN_ANALOG_INPUT_0 );
  int i_pin1 = analogRead( PIN_ANALOG_INPUT_1 );
  float f_pin0 = i_pin0 * 5.0 / 1023.0;
  float f_pin1 = i_pin1 * 5.0 / 1023.0;

  // 初期化："0"を受け取ると，その時の値をベースライン（＝0）とする
   if ( Serial.available() ) {
    char mode = Serial.read();
    switch (mode) {
      case '0' : 
          initial_pin0 = f_pin0;
          initial_pin1 = f_pin1;
        break;
      default: 
        break;
    }
  }
  f_pin0 -= initial_pin0;
  f_pin1 -= initial_pin1;
  
  //Serial.print( "pin0: " );
  Serial.print( f_pin0 );
  Serial.print("\t");
  //Serial.print( "pin1: " );
  Serial.print( f_pin1 );
  Serial.print("\n");  
  delay( 100 ); 
}
