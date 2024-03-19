#ifndef GYRO_H
#define GYRO_H
#include "constants.h"
#include <Arduino.h>
#include <Wire.h>

class Gyro
{
public:
  
  //mpu6050 variables and headers
  float previous_time, current_time;
  float theta_z;
  float callibrate_z;
  float callibrate_y;
  //gyroscope measure acceleration and angular 
  //velocity(this will not be in human redable form)
  int16_t gyro_x, gyro_y, gyro_z; //angular velocity
  float omega_x, omega_y, omega_z; //degrees per second
  int16_t acc_x, acc_y, acc_z; //angular velocity
  float acc_x_, acc_y_, acc_z_;
  /*
  setup will make all the necessary setup with wires
  to get the reading from the mpu
  */
  void setup_mpu();
  /*
  this will take the information from the gyro about
  the acc which will not be in human redable form
  and store those information in accel_x, accel_y, accel_z
  */

  /*this will call recordAccelRegisters, processAccelData
  recordGyroRegisters, processGyroDataand
  */
  void update();
};

// this tells the compiler that somewhere else in the program
// there will be defination for gyro
extern Gyro gyro;


#endif