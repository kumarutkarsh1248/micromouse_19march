// motor_imp.cpp
#include "motor.h"
#include "gyro.h"
#include "pid.h"
#include "distance.h"
#include "flood_fill.h"

extern long left_encoder_count;
extern long right_encoder_count;
// Define the external object of type motor
Motor motor;


void Motor::move_forward() {
  distance.update();
  float initial_time_loop = micros();
  float current_time_loop = micros();
  bool initial_front_right = false;
  bool initial_back_right = false;
  bool final_front_right = false;
  bool final_back_right = false;

  // while (((current_time_loop - initial_time_loop) / 1e6) < 2) {
  while (distance.distance_front > 5) {
    distance.update();
    initial_front_right = final_front_right;
    initial_back_right = final_back_right;
    final_front_right = distance.right_wall;
    final_back_right = distance.ir_value;
    if (!initial_front_right && initial_back_right && !final_front_right && !final_back_right) {
      delay(400);
      break;
    }




    // float error = pid.motor_control(0, fabs(distance.distance_left - distance.distance_right));

    int right_forward_speed = 40;
    int left_forward_speed = 40;
    // if (distance.right_wall  && distance.left_wall ) {
    // float error = pid.motor_control(0, fabs(distance.distance_left - distance.distance_right));

    //   if (distance.distance_right > distance.distance_left) {
    //     left_forward_speed += error;
    //     // right_forward_speed -= error;
    //   } else if (distance.distance_right < distance.distance_left) {
    //     // left_forward_speed -= error;
    //     right_forward_speed += error;
    //   }
    //   analogWrite(right_forward, right_forward_speed);
    //   analogWrite(left_forward, left_forward_speed);

    // }
    if (distance.right_wall) {
      float error = fabs(pid.motor_control(0, fabs(4 - distance.distance_right)));

      if (distance.distance_right > 4) {
        left_forward_speed += error;
        // right_forward_speed -= error;
      } else {
        // left_forward_speed -= error;
        right_forward_speed += error;
      }
      analogWrite(right_forward, right_forward_speed);
      analogWrite(left_forward, left_forward_speed);
    } else {
      analogWrite(right_forward, 40);
      analogWrite(left_forward, 40);
    }

    // Serial.print((current_time_loop - initial_time_loop) / 1e6);
    // Serial.print(", ");
    // Serial.print(left_encoder_count);
    // Serial.print(", ");
    // Serial.println(right_encoder_count);

    current_time_loop = micros();
  }
  analogWrite(right_forward, 0);
  analogWrite(left_forward, 0);
  pid.e_integral_motor = 0;

  if (bot.orientation == bot_front) {
    bot.y++;
  } else if (bot.orientation == bot_right) {
    bot.x++;
  } else if (bot.orientation == bot_left) {
    bot.x--;
  } else if (bot.orientation == bot_back) {
    bot.y--;
  }
  right_encoder_count = 0;
  left_encoder_count = 0;
}



void Motor::turn_left() {
  float initial_angle = 0;
  float final_angle = 0;
  gyro.previous_time = micros();
  gyro.current_time = micros();

  gyro.theta_z = 0;

  while (final_angle < 85) {
    float error = pid.gyro_control(90, gyro.theta_z);
    // float error = 50;

    //----------------------------------- gyro update ------------------------------
    gyro.update();
    gyro.current_time = micros();
    float dt = (gyro.current_time - gyro.previous_time) / 1e6;
    gyro.theta_z += gyro.omega_z * dt;
    gyro.previous_time = gyro.current_time;
    //-------------------------------------------------------------------------------
    final_angle = gyro.theta_z;
    // Serial.println(gyro.theta_z);

    int right_forward_speed = fabs(error);
    int left_backward_speed = fabs(error);

    analogWrite(right_forward, right_forward_speed);
    analogWrite(left_backward, left_backward_speed);
  }

  //make both the wheels static
  analogWrite(right_forward, 0);
  analogWrite(left_backward, 0);
  pid.e_integral_gyro = 0;

  if (bot.orientation == bot_front) {
    bot.orientation = bot_left;
  } else if (bot.orientation == bot_left) {
    bot.orientation = bot_back;
  } else if (bot.orientation == bot_back) {
    bot.orientation = bot_right;
  } else if (bot.orientation == bot_right) {
    bot.orientation = bot_front;
  }

  right_encoder_count = 0;
  left_encoder_count = 0;
}



void Motor::turn_right() {
  float initial_angle = 0;
  float final_angle = 0;
  gyro.previous_time = micros();
  gyro.current_time = micros();

  gyro.theta_z = 0;

  while (final_angle > -85) {
    float error = pid.gyro_control(-90, gyro.theta_z);
    // float error = 50;

    //----------------------------------- gyro update ------------------------------
    gyro.update();
    gyro.current_time = micros();
    float dt = (gyro.current_time - gyro.previous_time) / 1e6;
    gyro.theta_z += gyro.omega_z * dt;
    gyro.previous_time = gyro.current_time;
    //-------------------------------------------------------------------------------
    final_angle = gyro.theta_z;
    // Serial.println(gyro.theta_z);

    int right_backward_speed = fabs(error);
    int left_forward_speed = fabs(error);

    analogWrite(right_backward, right_backward_speed);
    analogWrite(left_forward, left_forward_speed);
  }

  //make both the wheels static
  analogWrite(right_backward, 0);
  analogWrite(left_forward, 0);
  pid.e_integral_gyro = 0;

  if (bot.orientation == bot_front) {
    bot.orientation = bot_right;
  } else if (bot.orientation == bot_right) {
    bot.orientation = bot_back;
  } else if (bot.orientation == bot_back) {
    bot.orientation = bot_left;
  } else if (bot.orientation == bot_left) {
    bot.orientation = bot_front;
  }

  right_encoder_count = 0;
  left_encoder_count = 0;
}


// Implement the print method
