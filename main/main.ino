


/* ESP8266 with motor shield
* This module serves as a motor controller and communication module
*/
//using namespace std;
//**********LIBRARIES************************************
#include "Arduino.h"
#include <jm_CPPM.h>
#include <PacketSerial.h>
//**********HEADERS**************************************
#include "motor.h"
//#include "servoControl.h"
#include "communication.h"
#include "platform.h"
#include "radio.h"
#include <Adafruit_SoftServo.h>
//*************INSTÄLLNIGNAR*****************************
//#define DEBUG_MOTORS 1
//#define DEBUG_SERVOS 1
//#define DEBUG_RADIO 1
//***********Globala variabler, bufferts och flaggor*****

//************WIFI*****************
char auth[] = "YourAuthToken";
char ssid[] = "NetworkName";
char pass[] = "NetworkPassword";
const char* mqtt_server = "your.MQTT.server.ip";
const char* mqtt_username = "yourMQTTusername";
const char* mqtt_password = "yourMQTTpassword";
const int mqtt_port = 1883;
/**************************** FOR OTA **************************************************/
#define SENSORNAME "porch" //change this to whatever you want to call your device
#define OTApassword "yourOTApassword" //the password you will need to enter to upload remotely via the ArduinoIDE
int OTAport = 8266;
/************* MQTT TOPICS **************************/
const char* light_state_topic = "walle";
const char* light_set_topic = "walle/set";
const char* on_cmd = "ON";
const char* off_cmd = "OFF";
//***********Controller Reciever******************
extern int joystick_x;
extern int joystick_y;
//***********Servos******************
int doorServoVal = 0;
int neckServoVal = 0;
int leftEyeServoVal = 0;
int rightEyeServoVal = 0;
int leftArmServoVal = 0;
int rightArmServoVal = 0;
//***********Communication******************

//***********Motor Sensors******************
int leftHallVal, rightHallVal;
int prev_leftHallVal = 0;
int prev_rightHallVal = 0;
int leftTime, cur_leftTime, rightTime, cur_rigthTime; //time variables
//***********Radio******************
//CPPM PIN 8
//

void setup()
{
  Serial.begin(9600);
  //setupMotors();
  //setupServos();
  //setupCommunication();
  //setupRadio();
  CPPM.begin();
}

void loop()
{
  cppm_cycle();
  handleSteering(joystick_x, joystick_y);
  //handleServos();

/*
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    switch(incomingByte){
      
    }
    /*
    Serial.print("y: ");
    Serial.print(joystick_y);
    Serial.print(", ");
    Serial.print("x: ");
    Serial.println(joystick_x);
    
  }*/
}
