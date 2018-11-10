#ifndef PLATFORM_H
#define PLATFORM_H

#include <Arduino.h>
#include "motor.h"
#include "radio.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "PID.h"
#include "debug.h"

class Platform
{
    double _speed;
    int _direction; //Internal direction
    int _heading;   //This is the compass reading

    //_x and _y are the input coordinated from the controller
    double _x;
    double _y;

  public:
    PID rotationPID;

    //The two motors on the current platform
    Motor rightMotor;
    Motor leftMotor;

    //The radio input handler
    Radio radioInput;

    Adafruit_HMC5883_Unified compass; // = Adafruit_HMC5883_Unified(12345);

  public:
    Platform(); //constructor
    void begin();

    void setSpeed(double speed);
    double getSpeed();
    void setDirection(int direction);
    int getDirection();
    void setHeading();
    int getHeading();

    void runMotors();     // Run the motors with their set speed
    void mapToMotors();   // Map _x and _y to the motors
    void readFromRadio(); // Read the input from the radio reciever

    void rotateTo(int setPoint);

    void displaySensorDetails();
};

#endif
