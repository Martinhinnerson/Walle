#include <Arduino.h>
#include "motor.h"

Motor::Motor()
{
  PWM_PIN = 0;
  DIR_PIN1 = 0;
  DIR_PIN2 = 0;
  HALL_PIN = 0;
  HallVal = 0;
  prev_HallVal = 0;
  Time = 0;
  Id = 0;
}

Motor::Motor(int pwm_pin, int dir_pin1, int dir_pin2, int hall_pin, int id)
{
  PWM_PIN = pwm_pin;
  DIR_PIN1 = dir_pin1;
  DIR_PIN2 = dir_pin2;
  HALL_PIN = hall_pin;

  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(HALL_PIN, INPUT);

  HallVal = 0;
  prev_HallVal = 0;
  Time = 0;
  Id = id;
}

void Motor::runMotor()
{
  if(_speed>=0){
    digitalWrite(DIR_PIN1, HIGH);
    digitalWrite(DIR_PIN2, LOW);
  } 
  else {
    digitalWrite(DIR_PIN1, LOW);
    digitalWrite(DIR_PIN2, HIGH);
  }
  int pulseWidth = 0;
  if (abs(_speed) >0.05) {
    pulseWidth = map(abs(_speed)*100, 0, 100, 50, 255);
  }

  Serial.println(pulseWidth);
  analogWrite(PWM_PIN, pulseWidth);
}

void Motor::setSpeed(double speed){
  _speed = speed;
}

int Motor::getSpeed(){
  return _speed;
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
