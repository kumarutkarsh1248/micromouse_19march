#include "distance.h"

Distance distance;

/*
this function will require only one pin and will
this pin as both output and input and give the distance
measured by the sensor in cm
*/
float Distance::find_distance(int pin)
{
  delay(10);
  //as trigger pin
  //for smooth high voltage we are first making it low
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(pin, LOW);

  //as echo pin
  pinMode(pin, INPUT);
  //time will be returned in microsecond
  float t = pulseIn(pin, HIGH);

  return t*0.017015;
  
}



void Distance::update() {
    distance_left = find_distance(left_distance_pin);
    distance_right = find_distance(right_distance_pin);
    distance_front = find_distance(front_distance_pin);
    right_wall = distance_right < 10 ? true : false;
    left_wall = distance_left < 10 ? true : false;
    front_wall = distance_front < 10 ? true : false;
    //when wall ir_falue is true when not wall ir value is false
    ir_value = digitalRead(ir_sensor) == HIGH ? false : true;
}

void Distance::check_wall()
{
  update();
  right_wall ? Serial.print(1) : Serial.print(0);
  Serial.print(", ");
  front_wall ? Serial.print(1) : Serial.print(0);
  Serial.print(", ");
  left_wall ? Serial.println(1) : Serial.println(0);
}






