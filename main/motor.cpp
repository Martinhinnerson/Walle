#include <Arduino.h>
#include "motor.h"
//#include "servo.h"

Motor::Motor()
{
  PWM_PIN = 0;
  DIR_PIN = 0;
  HALL_PIN = 0;
  HallVal = 0;
  prev_HallVal = 0;
  Time = 0;
  Id = 0;
}

Motor::Motor(int pwm_pin, int dir_pin, int hall_pin, int id)
{
  PWM_PIN = pwm_pin;
  DIR_PIN = dir_pin;
  HALL_PIN = hall_pin;

  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(HALL_PIN, INPUT);

  HallVal = 0;
  prev_HallVal = 0;
  Time = 0;
  Id = id;
}

void Motor::runMotor(double speed)
{
  if(speed>=0) digitalWrite(DIR_PIN, HIGH);
  else digitalWrite(DIR_PIN, LOW);
  int pulseWidth = 0;
  if (speed >0.05) {
    pulseWidth = map(abs(speed)*100, 0, 100, 50, 255);
  }

  Serial.println(pulseWidth);
  analogWrite(PWM_PIN, pulseWidth);
}

int Motor::readRpm()
{
  int rpm;
  int sig = analogRead(HALL_PIN); //read raw value of hall sensor
  HallVal = (sig > refsig); //convert it to digital 0,1 form
  if (prev_HallVal == 0 && HallVal == 1) { //check for rising edge
    curr_Time = micros();
    rpm = 1000000 * 60 / (curr_Time - Time);
    Serial.println("Motor: " + Id);
    Serial.println(rpm); //print the rpm
    Time = micros();
  }
  prev_HallVal = HallVal;
  return rpm;
}
