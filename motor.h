// motor.h
#ifndef MOTOR_H
#define MOTOR_H
#include "constants.h"

#include <Arduino.h>

class Motor {
    public:  
    void move_forward();
    void turn_left();
    void turn_right();
};

// Declare an external object of type motor
extern Motor motor;

#endif
