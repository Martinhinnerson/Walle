#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "settings.h"

/* Motor class
 * Used to once for each motor in the platform
 * 
 */
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

  int _id;
  int _regsig = 200; //for converting the analog signal coming from hall sensor to digital through arduino code

  double _speed = 0; //(-1 < speed < 1)

public:
  Motor();                                                              //Default constructor
  Motor(int pwm_pin, int dir_pin1, int dir_pin2, int hall_pin, int id); //Constructor
  void setSpeed(double speed);                                          //set the speed of the motor, (-1 < speed < 1)
  int getSpeed();                                                       //returns the current speed of the motor
  void runMotor();                                                      //Run the motor with dir and speed
  int readRpm();//! NOT IMPLEMENTED                                                        //read the rpm of the motor using hall sensor, NOT CURRENTLY ON THE ROBOT
};

#endif
