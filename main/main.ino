
/* ESP8266 with motor shield
* This module serves as a motor controller and communication module
*/
//using namespace std;
//**********INKLUDERINGAR**************************************
#include "Arduino.h"
#include "motor.h"
//#include "servoControl.h"
#include "communication.h"
#include "platform.h"
#include "radio.h"
#include <jm_CPPM.h>
//*************INSTÄLLNIGNAR*********************************************
#define rxBufferMax 100 //Storlek på buffer
#define rxCommandLength 100 //Längd på commando
//***********Globala variabler, bufferts och flaggor******************
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
int joystick_x = 512;
int joystick_y = 512;
//***********Servos******************
int doorServoVal = 0;
int neckServoVal = 0;
int leftEyeServoVal = 0;
int rightEyeServoVal = 0;
int leftArmServoVal = 0;
int rightArmServoVal = 0;
//***********Communication******************
volatile uint8_t rxBuffer[rxBufferMax]; //Buffer där senast mottagna datan ligger
char rxCommand[rxCommandLength + 1]; //När ett helt command mottagits sparas det här
volatile uint8_t rxCtr = 0; //håller reda på var i buffern vi är
volatile bool rxFlag = false; //true om vi fått ett nytt värde i buffern
volatile bool cxFlag = false; //sätts när "command-biten" har lästs i bussen,
// när den är satt kommer vi läsa det antal bitar som defineras i command-length
int incomingByte = 0; // FOR INCOMING SERIAL DATA FROM CONSOLE
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
  Serial.begin(115200);
  //setupMotors();
  //setupServos();
//  setupCommunication();
  //setupRadio();
  CPPM.begin();
}

void loop()
{
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch(incomingByte){
      case 119://up
      if(joystick_y<=1012) joystick_y += 10;
      break;
      case 97://left
      if(joystick_x>=12) joystick_x -= 10;
      break;
      case 115://down
      if(joystick_y>=12) joystick_y -= 10;
      break;
      case 100://right
      if(joystick_x<=1012) joystick_x += 10;
      break;

    }
    /*
    Serial.print("y: ");
    Serial.print(joystick_y);
    Serial.print(", ");
    Serial.print("x: ");
    Serial.println(joystick_x);
    */
  }
  //cppm_cycle();
  if (CPPM.synchronized())
  {
    joystick_y = CPPM.read_us(CPPM_THRO) - 1500;
    Serial.println(joystick_y);
    joystick_x = CPPM.read_us(CPPM_ELEV) - 1500; // rudder
  //Serial.println(rudd);
  }

    handleSteering(joystick_x, joystick_y);

}
