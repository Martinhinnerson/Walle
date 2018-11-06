#include <Arduino.h>
#include "platform.h"
#include "motor.h"
#include "math.h"

//This is old before the platform was turned into a class
//volatile Motor motor2(3, 2, 4, A1, 1); //PWM DIR1 DIR2 HALL ID
//volatile Motor motor1(6, 7, 5, A0, 0);

Platform::Platform()
{
    _speed = 0;
    _direction = 0;
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

void Platform::handleDriveFromRadio(int joystick_x, int joystick_y)
{
    radioInput.updateRadio();
    //Map to -1, 1
    double x = double(map(radioInput.getJoysticX(), -514, 514, -100, 100)) / 100;
    double y = double(map(radioInput.getJoysticY(), -514, 514, -100, 100)) / 100;

    //Convert to polar
    double r = hypot(y, x);
    double t = atan2(y, x);

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
    Serial.print(y);
    Serial.print(", ");
    Serial.println(x);
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