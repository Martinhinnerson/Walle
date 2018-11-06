/* This is the main file for the robot module. */
//**********LIBRARIES************************************
#include "Arduino.h"
#include <jm_CPPM.h>
#include <PacketSerial.h>
//**********HEADERS**************************************
#include "motor.h"
#include "communication.h"
#include "platform.h"
#include "radio.h"
//*************SETTINGS*****************************
//#define DEBUG_MOTORS 1
//#define DEBUG_SERVOS 1
//#define DEBUG_RADIO 1
//***********Controller Reciever******************

//***********Communication******************

//***********Platform******************
Platform walle; // instansiate the platform with the default constructor

void setup()
{
  Serial.begin(9600);
  CPPM.begin();
}

void loop()
{
  walle.readFromRadio();
  walle.mapToMotors();
  walle.runMotors();
}
