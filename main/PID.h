#ifndef PID_H
#define PID_H

#include <Arduino.h>


class PID
{
  private:
    float _Kp, _Ki, _Kd, T_s;
    bool _cfg_err; //Error that can be set if something is wrong

    float _control_k_1; // Controlsignal for k-1
    float _err_k_1; // Error for k-1
    float _err_k_2; // Error for k-2


  private:
    void setCfgErr();

  public:
    PID();
    PID(float kp, float ki, float kd);

    void clear();
    bool setCoefficients(float kp, float ki, float kd);

    float calculate(float setPoint, float feedback);

    bool err();

};

#endif