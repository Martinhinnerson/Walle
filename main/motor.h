#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
  //Motor Pins
  int PWM_PIN;
  int DIR_PIN;
  //Hall sensor variables
  int HALL_PIN;
  int HallVal, prev_HallVal;
  int Time, curr_Time; //time variables

  int Id;
  int refsig = 200; //for converting the analog signal coming from hall sensor to digital through arduino code

public:

  Motor();
  Motor(int pwm_pin, int dir_pin, int hall_pin, int id); //Constructor
  void runMotor(double speed);//Run the motor with dir and speed
  int readRpm();//read the rpm of the motor using hall sensor
};

#endif
