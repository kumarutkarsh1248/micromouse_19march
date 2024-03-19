#include "gyro.h"
Gyro gyro;

void Gyro::update() {
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05); 
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B); 
  Wire.write(0x8); 
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();
  omega_x = (float)gyro_x/65.5; //not calibrated yet
  omega_y = (float)gyro_y/65.5; //not calibrated yet
  omega_z = (float)gyro_z/65.5;
}
// void Gyro::update()
// {
// Wire.beginTransmission(0x68);
//   Wire.write(0x1A);
//   Wire.write(0x05);
//   Wire.endTransmission();
//   Wire.beginTransmission(0x68);
//   Wire.write(0x1C);
//   Wire.write(0x10);
//   Wire.endTransmission();
//   Wire.beginTransmission(0x68);
//   Wire.write(0x3B);
//   Wire.endTransmission(); 
//   Wire.requestFrom(0x68,6);
//   int16_t acc_x = Wire.read() << 8 | Wire.read();
//   int16_t acc_y = Wire.read() << 8 | Wire.read();
//   int16_t acc_z = Wire.read() << 8 | Wire.read();
//   Wire.beginTransmission(0x68);
//   Wire.write(0x1B); 
//   Wire.write(0x8);
//   Wire.endTransmission();                                                   
//   Wire.beginTransmission(0x68);
//   Wire.write(0x43);
//   Wire.endTransmission();
//   Wire.requestFrom(0x68,6);
//   int16_t gryo_x=Wire.read()<<8 | Wire.read();
//   int16_t gyro_y=Wire.read()<<8 | Wire.read();
//   int16_t gyro_z=Wire.read()<<8 | Wire.read();
//   omega_x=(float)gryo_x/65.5;
//   omega_y=(float)gyro_y/65.5;
//   omega_z=(float)gyro_z/65.5;
//   acc_x_=(float)acc_x/4096;
//   acc_y_=(float)acc_y/4096;
//   acc_z_=(float)acc_z/4096;
//   // AngleRoll=atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
//   // AnglePitch=-atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
// }

void Gyro::setup_mpu(){
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68); 
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for(int i = 0; i<2000; i++)
  {
    update();
    callibrate_z += omega_z;
    callibrate_y += acc_y_;
    delay(1);
  }
  callibrate_z = callibrate_z / 2000;
  callibrate_y = callibrate_y / 2000;
}