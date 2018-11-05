#ifndef PLATFORM_H
#define PLATFORM_H

#include <Arduino.h>
#include "motor.h"

void runMotors();
void handleDriveFromRadio(int joystick_x, int joystick_y);
#endif
