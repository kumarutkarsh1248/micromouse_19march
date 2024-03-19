// motor.h
#ifndef DISTANCE_H
#define DISTANCE_H
#include "constants.h"

#include <Arduino.h>

class Distance
{
  public:
  float find_distance(int pin);
  void update();
  void check_wall();
  float distance_left, distance_right, distance_front;
  bool right_wall, left_wall, front_wall, ir_value;
};

// Declare an external object of type pid
extern Distance distance;

#endif
