// 空気圧＋角度＋角速度＋角加速度

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "HX711.h"
const int AIRPRESS_1_DAT = 9;
const int AIRPRESS_1_CLK = 8;
const int AIRPRESS_2_DAT = 7;
const int AIRPRESS_2_CLK = 6;

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

// for ajust angle
double initial_yaw = 0;
double initial_pitch = 0;

// for acceleration
unsigned long times, old_times;
double delta;
double pre_yaw;
double pre_pitch;
double pre_gyro_yaw;
double pre_gyro_pitch;

// for airpress
HX711 scale1;
HX711 scale2;
char data[100];

int sign(double x) {
  int value = 0;
  if (x > 0)
    value = 1;
  else if (x < 0)
    value = -1;

  return value;
}


void setup() {
  Serial.begin(9600);
  
  // Gyro setup ///////////////////////////////////////////
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  bno.setExtCrystalUse(true);

  // Air press setup //////////////////////////////////////
  scale1.begin(AIRPRESS_1_DAT, AIRPRESS_1_CLK);
  scale1.set_scale(386.3);
  scale1.tare();
  scale2.begin(AIRPRESS_2_DAT, AIRPRESS_2_CLK);
  scale2.set_scale(386.3);
  scale2.tare();
}


void loop()
{
  /* Get a new sensor event */
  imu::Quaternion quat = bno.getQuat();
  double ysqr = quat.y() * quat.y();

  // pitch (y-axis rotation)
  double t2 = +2.0 * (quat.w() * quat.y() - quat.x() * quat.z());
  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;
  double pitch = asin(t2) * 180 / PI;

  // yaw (z-axis rotation)
  double t3 = +2.0 * (quat.w() * quat.z() + quat.x() * quat.y());
  double t4 = +1.0 - 2.0 * (ysqr + quat.z() * quat.z());
  double yaw = atan2(t3, t4) * 180 / PI;

  // Reset origin：Unity側から"0"を受け取ると，その姿勢を原点とした角度に設定
  if ( Serial.available() ) {
    char mode = Serial.read();
    switch (mode) {
      case '0' : 
        initial_pitch = pitch;
        initial_yaw = yaw;
        break;
      default: 
        break;
    }
  }
  pitch = pitch - initial_pitch;
  yaw = yaw - initial_yaw;

  // Adjust from -180 to 180
  while (abs(pitch) > 180) {
    pitch -= sign(pitch) * 360;
  }

  while (abs(yaw) > 180) {
    yaw -= sign(yaw) * 360;
  }

  /* New line for the next sample */
  Serial.println("");

  // Angle //////////////////////////////////////////
  Serial.print(pitch);
  Serial.print("\t");
  Serial.print(yaw);
  Serial.print("\t");

  // Air press //////////////////////////////////////
  if (scale1.is_ready()) {
    long reading1 = scale1.get_units();
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
    if(reading2==0){
      Serial.print(1);    //0で割り算できないのを防ぐ
    }
    else{
      Serial.print(reading2);
    }
  } 
  Serial.print("\t");

  // Angular velocity /////////////////////////////////
  imu::Vector<3> gyroscope = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  //  Serial.print(gyroscope.z());    //pitch_gyro
  //  Serial.print("\t");
  Serial.print(gyroscope.y());    //yaw_gyro
  Serial.print("\t");

  // Angular acceleration /////////////////////////////
  times = millis();
  delta = (double)(times - old_times)/1000;   //secに変換
  old_times = times;
  double accel_pitch = (gyroscope.z() - pre_gyro_pitch)/delta;
  double accel_yaw = (gyroscope.y() - pre_gyro_yaw)/delta;
  pre_gyro_pitch = gyroscope.z();
  pre_gyro_yaw = gyroscope.y();
  //  Serial.print(accel_pitch);
  //  Serial.print("\t");
  Serial.print(accel_yaw);
  Serial.print("\n");
  
  delay(100);
}
