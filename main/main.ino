#include <TFMini.h>

/* This is the main file for the robot module. */
//**********LIBRARIES************************************
#include "Arduino.h"
#include <jm_CPPM.h>
#include <PacketSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
//**********HEADERS**************************************
#include "motor.h"
#include "communication.h"
#include "platform.h"
#include "radio.h"
//*************SETTINGS*****************************
//#define DEBUG_MOTORS 1
//#define DEBUG_SERVOS 1
//#define DEBUG_RADIO 1
//#define DEBUG_COMPASS 1
//***********Controller Reciever******************

//***********Communication******************

//***********Platform******************
Platform walle; // instansiate the platform with the default constructor
//Adafruit_HMC5883_Unified compass = Adafruit_HMC5883_Unified(12345);

void setup()
{
  Serial.begin(115200);
  CPPM.begin();

  walle.begin();
  
}


int heading;

/* Main loop */
void loop()
{
  walle.readFromRadio();
  walle.mapToMotors();
  walle.runMotors();
  walle.setHeading();

  //Serial.println(walle.getHeading());
  
}