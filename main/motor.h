#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
  //Motor Pins
  int PWM_PIN;
  int DIR_PIN1;
  int DIR_PIN2;
  //Hall sensor variables
  int HALL_PIN;
  int HallVal, prev_HallVal;
  int Time, curr_Time; //time variables

  int Id;
  int refsig = 200; //for converting the analog signal coming from hall sensor to digital through arduino code

  double _speed = 0;

public:

  Motor();
  Motor(int pwm_pin, int dir_pin1, int dir_pin2, int hall_pin, int id); //Constructor
  void runMotor();//Run the motor with dir and speed
  int readRpm();//read the rpm of the motor using hall sensor
  void setSpeed(double speed);
  int getSpeed();
};

#endif
