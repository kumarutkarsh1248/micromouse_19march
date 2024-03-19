#include "pid.h"

// Define the external object of type motor
Pid pid;

float Pid::motor_control(int target, int current_state)
{
  long previous_time_motor = 0;
  float e_previous_motor = 0;
  // float e_integral_motor = 0;
  
  //measuring the time elapsed since the last iteration
  long current_time_motor = micros();
  float delta_T = (float(current_time_motor - previous_time_motor)) / 1.0e6;
  
  //computer the error, derivative and integral
  int e = target - current_state;
  float e_derivative = (e - e_previous_motor) / delta_T;
  e_integral_motor = e_integral_motor + e * delta_T;

  //compute the pid control signal
  float u = (kp_motor * e) + (kd_motor * e_derivative) + (ki_motor * e_integral_motor) + 40;

  //update variable for the next iteration
  previous_time_motor = current_time_motor;
  e_previous_motor = e;

  return u;
}

float Pid::gyro_control(int target, int current_state)
{
  long previous_time_gyro = 0;
  float e_previous_gyro = 0;
  // float e_integral_gyro = 0;
  // float kp_gyro = 1;
  // float ki_gyro = 0.2;
  // float kd_gyro = 0.0;
  
  //measuring the time elapsed since the last iteration
  long current_time_gyro = micros();
  float delta_T = (float(current_time_gyro - previous_time_gyro)) / 1.0e6;
  
  //computer the error, derivative and integral
  int e = target - current_state;
  float e_derivative = (e - e_previous_gyro) / delta_T;
  e_integral_gyro = e_integral_gyro + e * delta_T;

  //compute the pid control signal
  float u = (kp_gyro * e) + (kd_gyro * e_derivative) + (ki_gyro * e_integral_gyro);

  //update variable for the next iteration
  previous_time_gyro = current_time_gyro;
  e_previous_gyro = e;

  return u;
}