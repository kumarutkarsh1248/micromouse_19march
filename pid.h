// motor.h
#ifndef PID_H
#define PID_H
#include "constants.h"
#include <Arduino.h>

class Pid
{
  public:

  //variable for pid control
  // long previous_time_motor = 0;
  // float e_previous_motor = 0;
  float e_integral_motor = 0;
  float kp_motor = 5;
  float ki_motor = 0;
  float kd_motor = 0;

  // long previous_time_gyro = 0;
  // float e_previous_gyro = 0;
  float e_integral_gyro = 0;
  float kp_gyro = 1.8; //1.8; 
  float ki_gyro = 0.00;
  float kd_gyro = 0.0;



  /*
  @ target => counts of the right motor
  @ current_state => counts of the left motor
  */
  float motor_control(int target, int current_state); 

  /*
  @ target => 90 degrees for left or right turn and 180 
    degree for back turn
  @ current_state => current orientation of the bot
  */ 
  float gyro_control(int target, int current_state);
};

// Declare an external object of type pid
extern Pid pid;

#endif
