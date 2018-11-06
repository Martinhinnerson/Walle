#ifndef PLATFORM_H
#define PLATFORM_H

#include <Arduino.h>
#include "motor.h"
#include "radio.h"

class Platform
{
    double _speed;
    int _direction;

    Motor rightMotor;
    Motor leftMotor;

    Radio radioInput;

public:
    Platform();//constructor

    void setSpeed(double speed);
    double getSpeed();
    void setDirection(int direction);
    int getDirection();
    
    void runMotors();
    void handleDriveFromRadio(int joystick_x, int joystick_y);
};


#endif
