#include <Arduino.h>
#include "platform.h"
#include "motor.h"
#include "math.h"


volatile Motor motor1(5, 0, A0, 0);
volatile Motor motor2(4, 2, A1, 1);


void handleSteering(int joystick_x, int joystick_y)
{

//Map to -1, 1
double x = double(map(joystick_x, -514, 514, -100, 100))/100;
double y = double(map(joystick_y, -514, 514, -100, 100))/100;
Serial.print("Mapped: ");
Serial.print(y);
Serial.print(", ");
Serial.println(x);
//Convert to polar
double r = hypot(y, x);
double t = atan2(y, x);
Serial.print("Radius and angle: ");
Serial.print(r);
Serial.print(", ");

//rotate by 45 degrees
t -= 3.14 / 4;
Serial.println(t);
//convert back to cartesian
double left = r * cos(t);
double right = r * sin(t);

//rescale the new coordinates
left = left * sqrt(2);
right = right * sqrt(2);

//Clamp to -1/+1
left = max(-1, min(left, 1));
right = max(-1, min(right, 1));

motor1.runMotor(left);
motor2.runMotor(right);

Serial.print("Left: ");
Serial.print(left);
Serial.print(", ");
Serial.print("Right: ");
Serial.println(right);

}
