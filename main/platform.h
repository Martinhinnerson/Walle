#ifndef PLATFORM_H
#define PLATFORM_H

#include <Arduino.h>
#include "motor.h"
#include "radio.h"

class Platform
{
    double _speed;
    int _direction;

    //_x and _y are the input coordinated from the controller
    double _x;
    double _y;

    //The two motors on the current platform
    Motor rightMotor;
    Motor leftMotor;

    //The radio input handler
    Radio radioInput;

public:
    Platform();//constructor

    void setSpeed(double speed);
    double getSpeed();
    void setDirection(int direction);
    int getDirection();
    
    void runMotors(); // Run the motors with their set speed
    void mapToMotors(); // Map _x and _y to the motors
    void readFromRadio(); // Read the input from the radio reciever
};


#endif
