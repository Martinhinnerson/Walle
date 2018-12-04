#ifndef PLATFORM_H
#define PLATFORM_H

#include <Arduino.h>
#include "motor.h"
#include "radio.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "PID.h"
#include "settings.h"
#include "timer.h"
#include <jm_CPPM.h>
#include <TFMini.h>
#include <PacketSerial.h>
#include <AccelStepper.h>

//Cutoff everything outside of -1 < a < 1
#define CUTOFF1(a) max(-1, min(a, 1))

class Platform
{
    double _speed;
    int _direction; //Internal direction
    int _heading;   //This is the compass reading

    //_x and _y are the input coordinated from the controller
    double _x;
    double _y;

    //The mode the platform is currently in
    int _mode;

  public:
    PID rotationPID;

    //The two motors on the current platform
    Motor rightMotor;
    Motor leftMotor;

    //Stepper motor
    AccelStepper sensorStepper;

    //The radio input handler
    Radio radioInput;

    //Magnetometer sensor
    Adafruit_HMC5883_Unified compass; // = Adafruit_HMC5883_Unified(12345);

    //Timers
    Timer motorTimer; // timer for the motor updates
    Timer PIDTimer; // timer for PID loop
    Timer radioTimer; // timer for the radio


    // Serial port definitions
    HardwareSerial *DebugSerial = &Serial;
    HardwareSerial *MainSerial = &Serial1;

  public:
    Platform(); //constructor
    void begin();

    void run(); //main loop of the platform, should be run in loop()

    void setSpeed(double speed);
    double getSpeed();
    void setDirection(int direction);
    int getDirection();
    int getHeading();
    void setMode(int mode);
    int getMode();

    void runMotors();     // Run the motors with their set speed
    void mapToMotors();   // Map _x and _y to the motors
    void readFromRadio(); // Read the input from the radio reciever

    void rotateTo(int setPoint);

    void displaySensorDetails();

    void readSerial();
    void readCommand(String input);
};

#endif