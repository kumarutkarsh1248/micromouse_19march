#include "distance.h"
#include "gyro.h"
#include "constants.h"
#include "motor.h"
#include "flood_fill.h"

Cell maze[SIZE][SIZE];
Bot bot;

//variable
long right_encoder_count = 0;
long left_encoder_count = 0;
void handle_encoder_right() {
  right_encoder_count++;
}
void handle_encoder_left() {
  left_encoder_count++;
}


void setup() {
  Serial.begin(115200);
  pinMode(ir_sensor, INPUT);
  gyro.setup_mpu();
  set_boundary_wall();
  bot_update_wall();
  
  pinMode(right_encoder_pin, INPUT);
  pinMode(left_encoder_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(right_encoder_pin), handle_encoder_right, RISING);
  attachInterrupt(digitalPinToInterrupt(left_encoder_pin), handle_encoder_left, RISING);

}

float i_velocity, f_velocity;
float distance_y;
void loop() {
  //=============gyro
  gyro.update();
  gyro.current_time = micros();
  float dt = (gyro.current_time - gyro.previous_time) / 1e6;
  gyro.theta_z += (gyro.omega_z - gyro.callibrate_z) * dt;
  gyro.previous_time = gyro.current_time;

  distance.update();
  // Serial.print(distance.distance_left);
  // Serial.print(", ");
  // Serial.print(distance.distance_front);
  // Serial.print(", ");
  // Serial.println(distance.distance_right);
  // Serial.print(", ");
  // Serial.print(gyro.omega_z - gyro.callibrate_z);
  // Serial.print(", ");
  // Serial.println(gyro.theta_z);
  // Serial.print(", ");
  // Serial.print(right_encoder_count);
  // Serial.print(", ");
  // Serial.println(left_encoder_count);

  distance.right_wall ? Serial.println(1) : Serial.println(0);
  // Serial.print(", ");
  // Serial.println(distance.distance_right);
 
  // delay(2000);
  // motor.move_forward();
  // delay(2000);


  //====================flooD_fILL_ALGO======================
  // if ((where_to_move(bot.x, bot.y) == cell_front && bot.orientation == bot_front) || (where_to_move(bot.x, bot.y) == cell_right && bot.orientation == bot_right) || (where_to_move(bot.x, bot.y) == cell_left && bot.orientation == bot_left) || (where_to_move(bot.x, bot.y) == cell_back && bot.orientation == bot_back)) {
  //   motor.move_forward();
  //   bot_update_wall();
  //   whole_flood_fill();
  // } else if ((where_to_move(bot.x, bot.y) == cell_front && bot.orientation == bot_left) || (where_to_move(bot.x, bot.y) == cell_right && bot.orientation == bot_front) || (where_to_move(bot.x, bot.y) == cell_back && bot.orientation == bot_right) || (where_to_move(bot.x, bot.y) == cell_left && bot.orientation == bot_back)) {
  //   motor.turn_right();
  // } else if ((where_to_move(bot.x, bot.y) == cell_front && bot.orientation == bot_right) || (where_to_move(bot.x, bot.y) == cell_right && bot.orientation == bot_back) || (where_to_move(bot.x, bot.y) == cell_back && bot.orientation == bot_left) || (where_to_move(bot.x, bot.y) == cell_left && bot.orientation == bot_front)) {
  //   // al.println(maze[bot.x][bot.y].config);
  //   motor.turn_left();
  // } else if ((where_to_move(bot.x, bot.y) == cell_front && bot.orientation == bot_back) || (where_to_move(bot.x, bot.y) == cell_right && bot.orientation == bot_left) || (where_to_move(bot.x, bot.y) == cell_back && bot.orientation == bot_front) || (where_to_move(bot.x, bot.y) == cell_left && bot.orientation == bot_right)) {
  //   // Serial.println(maze[bot.x][bot.y].config);
  //   motor.turn_left();
  //   motor.turn_left();
  // }

  //===============my algo==================
  // distance.update();
  // if(distance.front_wall)
  // {
  //   if(!distance.right_wall)
  //   {
  //     motor.turn_right();
  //     distance.update();
  //   }
  //   else if(!distance.left_wall)
  //   {
  //     motor.turn_left();
  //     distance.update();
  //   }
  //   else
  //   {
  //     motor.turn_right();
  //     distance.update();
  //     motor.turn_right();
  //     distance.update();
  //   }
  // }
  // motor.move_forward();
  // distance.update();



  //==================================mms logo
  distance.update();
  if(!distance.right_wall)
  {
    motor.turn_right();
    distance.update();
  }
  while(distance.front_wall)
  {
    motor.turn_left();
    distance.update();
  }
  motor.move_forward();
  distance.update();
  // motor.move_forward();
  // delay(2000);
  // motor.turn_right();
  // delay(2000);
  // motor.turn_left();
  // delay(2000);

}
