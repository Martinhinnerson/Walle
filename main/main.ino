
/* This is the main file for the robot module. */
//**********LIBRARIES************************************
#include <Arduino.h>
//**********HEADERS**************************************
#include "platform.h"
//*******************************************************
Platform walle; // instansiate the platform with the default constructor

void setup()
{
  walle.begin();
}

void loop()
{
  walle.run();
}