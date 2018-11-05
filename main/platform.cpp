#include <Arduino.h>
#include "platform.h"
#include "motor.h"
#include "math.h"

extern int joystick_rot;

volatile Motor motor2(3, 2, 4, A1, 1); //PWM DIR1 DIR2 HALL ID
volatile Motor motor1(6, 7, 5, A0, 0);

void runMotors(){
    motor1.runMotor();
    motor2.runMotor();
}

void handleDriveFromRadio(int joystick_x, int joystick_y)
{
    //Map to -1, 1
    double x = double(map(joystick_x, -514, 514, -100, 100)) / 100;
    double y = double(map(joystick_y, -514, 514, -100, 100)) / 100;
#ifdef DEBUG_MOTORS
    Serial.print("Mapped: ");
    Serial.print(y);
    Serial.print(", ");
    Serial.println(x);
#endif
    //Convert to polar
    double r = hypot(y, x);
    double t = atan2(y, x);
#ifdef DEBUG_MOTORS
    Serial.print("Radius and angle: ");
    Serial.print(r);
    Serial.print(", ");
#endif
    //rotate by 45 degrees
    t -= 3.14 / 4;
#ifdef DEBUG_MOTORS
    Serial.println(t);
#endif
    //convert back to cartesian
    double left = r * cos(t);
    double right = r * sin(t);

    //rescale the new coordinates
    left = left * sqrt(2);
    right = right * sqrt(2);

    //Clamp to -1/+1
    left = max(-1, min(left, 1));
    right = max(-1, min(right, 1));

    motor1.setSpeed(left);
    motor2.setSpeed(right);

#ifdef DEBUG_MOTORS
    Serial.print("Left: ");
    Serial.print(left);
    Serial.print(", ");
    Serial.print("Right: ");
    Serial.println(right);
#endif
}
