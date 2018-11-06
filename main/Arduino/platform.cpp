#include <Arduino.h>
#include "platform.h"
#include "motor.h"
#include "math.h"

Platform::Platform()
{
    _speed = 0;
    _direction = 0;
    _x = 0;
    _y = 0;
    rightMotor = Motor::Motor(3, 2, 4, A1, 1);
    leftMotor = Motor::Motor(6, 7, 5, A0, 0);
    radioInput = Radio::Radio();
}

void Platform::setSpeed(double speed)
{
    _speed = speed;
}
double Platform::getSpeed()
{
    return _speed;
}
void Platform::setDirection(int direction)
{
    _direction = direction;
}
int Platform::getDirection()
{
    return _direction;
}

void Platform::runMotors()
{
    rightMotor.runMotor();
    leftMotor.runMotor();
}

void Platform::readFromRadio()
{
    radioInput.updateRadio();
        //Map to -1, 1
    _x = double(map(radioInput.getJoysticX(), -514, 514, -100, 100)) / 100;
    _y = double(map(radioInput.getJoysticY(), -514, 514, -100, 100)) / 100;
}

void Platform::mapToMotors()
{
    //Convert to polar
    double r = hypot(_y, _x);
    double t = atan2(_y, _x);

    //rotate by 45 degrees
    t -= 3.14 / 4;

    //convert back to cartesian
    double left = r * cos(t);
    double right = r * sin(t);

    //rescale the new coordinates
    left = left * sqrt(2);
    right = right * sqrt(2);

    //Clamp to -1/+1
    left = max(-1, min(left, 1));
    right = max(-1, min(right, 1));

    leftMotor.setSpeed(left);
    rightMotor.setSpeed(right);

#ifdef DEBUG_MOTORS
    Serial.print("Mapped: ");
    Serial.print(_y);
    Serial.print(", ");
    Serial.println(_x);
    Serial.print("Radius and angle: ");
    Serial.print(r);
    Serial.print(", ");
    Serial.println(t);
    Serial.print("Left: ");
    Serial.print(left);
    Serial.print(", ");
    Serial.print("Right: ");
    Serial.println(right);
#endif
}