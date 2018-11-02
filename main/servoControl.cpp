#include <Arduino.h>
#include "servoControl.h"
//#include "servo.h"
/*
  Servo::Servo(int pwm_pin, int startAngle, int id){
    _startAngle = startAngle;
    _id = id;
    PWM_PIN = pwm_pin;
    pinMode(PWM_PIN, OUTPUT);
    _angle = _startAngle;
  }

  void Servo::setAngle(int angle){
    _angle = angle;
  }

  int Servo::getAngle(){
    return _angle;
  }

  void Servo::gotoAngle(){
    byte pwmOut = map(_angle, 0, 360, 5, 250);
    Serial.println(pwmOut);
    analogWrite(PWM_PIN, pwmOut);
  }*/