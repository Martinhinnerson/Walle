
/* This is the main file for the robot module. */
//**********LIBRARIES************************************
#include <Arduino.h>
//**********HEADERS**************************************
#include "platform.h"
#include "settings.h"
//*******************************************************
Platform walle; // instansiate the platform with the default constructor

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Initializing Walle...");
  delay(100);
  walle.begin();
  delay(1000);
  Serial.println("Walle initialized.");
}

void loop()
{
  //Serial.println(millis());
  walle.run();
}