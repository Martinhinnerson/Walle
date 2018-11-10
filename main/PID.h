#ifndef PID_H
#define PID_H

#include <Arduino.h>


class PID
{
  private:
    float _p, _i, _d;
    bool _cfg_err; //Error that can be set if something is wrong

    float _sum;
    float _last_sp, _last_out, _last_err;


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