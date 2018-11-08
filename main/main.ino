//#include <Adafruit_HMC5883_U.h>
#include <Wire.h>
#define address 0x1E
//Global variables
int x,y,z;                   //Variables used to hold the triple axis data

int xCal=0, yCal=0, zCal=0;  //Variables used to calibrate the triple axis data.
int calValue = 1000; //On startup, all axis variables will equal this number.

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
  Serial.begin(115200);
  CPPM.begin();

    Wire.begin();

  //Setup the magnetometer 
  magSetting(0x00, B01101000); // Magnetometer settings associated with Register A. See datasheet for acceptable values. 
  magSetting(0x01, B01100000); // Magnetometer settings associated with Register B. See datasheet for acceptable values. 
  calibrateMag(); // Set or calibrate all axis variables to the calValue. 
}

/* Main loop */
void loop()
{
  //walle.readFromRadio();
  //walle.mapToMotors();
  //walle.runMotors();
  getReadings();
  printReadings();

}

//=====================================================================================================
// magSetting(regLoc, setting):
//    regLoc: is the register address location that we want to interact with (RegA = 0x00, RegB = 0x01, Mode = 0x02)
//    setting: is the 8bit code used to configure the magnetometer (see datasheet)
//
//    This function allows you to configure the magnetometer to suit your specific application
//    A delay of 10 is used, but anything above 7 is recommended.
//-----------------------------------------------------------------------------------------------------
void magSetting(byte regLoc, byte setting){
  Wire.beginTransmission(address);
  Wire.write(regLoc); 
  Wire.write(setting);
  Wire.endTransmission();
  delay(10);
}


//=====================================================================================================
// getReadings():
//    It is necessary to send the bytes (0x02 and 0x01) to instruct the magnetometer to prepare for single measurement mode
//    Request 6 bytes from the magnetometer and then read 2 bytes per axis (assigned to variables x, y and z).
//    The xCal, yCal, and zCal variables adjust the magnetometer's readings relative to it's initial state.
//    Set the global "calValue" variable to 0 if you don't want to "calibrate" the magnetometer on startup.
//    The magnetometer should send back 6 bytes of positional data, if not, an Error message will be printed to the serial monitor
//-----------------------------------------------------------------------------------------------------
void getReadings(){
  magSetting(0x02, 0x01);        //prepare to take reading (Single measurement mode) - this populates the registers with data
  Wire.requestFrom(address, 6);  //Request 6 bytes. Each axis uses 2 bytes.
  if (Wire.available()>5){
     x = readValue()- xCal;
     z = readValue()- zCal;
     y = readValue()- yCal;    
  } else {
    Serial.println("****Error: Less than 6 bytes available for reading*****");
  }
}


//=====================================================================================================
// readValue():
//    This reads the magnetometer's data registers - 2 bytes at a time.
//    All 6 data registers must be read properly before new data can be placed into any of these data registers
//    This function reads two bytes (8bit + 8bit) and joins them together to make a 16bit integer value.
//    This value is returned and assigned to one of the axis variables x, y and/or z.
//    With every read() called, the data register pointer is incremented.
//    When magSetting(0x02, 0x01) is called in the getReadings() function, the pointer is reset to the first data register (03).
//-----------------------------------------------------------------------------------------------------
int readValue(){
  int val = Wire.read()<<8; 
      val |= Wire.read();

  return val;
}


//=====================================================================================================
// printReadings():
//    This funtion is used to print the 3 axis values (x, y and z) to the Serial monitor window.
//-----------------------------------------------------------------------------------------------------
void printReadings(){
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
}


//=====================================================================================================
// calibrateMag():
//    This function is used to calibrate or set each axis value to calValue.
//    calValue is defined in the global variables section (=1000)
//    After calibration, each axis variable (x, y and z) will equal the calValue, no matter what position the magnetometer is in.
//-----------------------------------------------------------------------------------------------------
void calibrateMag(){
  getReadings();
  xCal = x-calValue;
  yCal = y-calValue;
  zCal = z-calValue;
}