#include "PID.h"
#include <Arduino.h>

PID::PID()
{
    clear();
}

PID::PID(float kp, float ki, float kd)
{
    setCoefficients(kp, ki, kd);
}

void PID::clear()
{
    _p = 0;
    _i = 0;
    _d = 0;
    _cfg_err = false;
}

bool PID::setCoefficients(float kp, float ki, float kd)
{
    _p = kp;
    _i = ki;
    _d = kd;
    return !_cfg_err;
}

void PID::setCfgErr()
{
    _cfg_err = true;
    _p = _i = _d = 0;
}

//Error that can be set if something is wrong
//This is for set if something is wrong in the setup
bool PID::err()
{
    return _cfg_err;
}

//This function will most likely vary depending on what we want to control
float PID::calculate(float sp, float fb)
{

    float err = sp - fb; 
    MOD(err); //The modulo function defined in PID.h wraps around the value because
    //we always want to rotate the closest direction

    float P = 0, I = 0, D = 0;

    if (_p)
    {
        P = _p * err;
    }

    if (_i)
    {
        _sum += err * _i; 
        I = _sum;
    }

    if (_d)
    {
        float deriv = (err - _last_err) - (sp - _last_sp);
        _last_sp = sp;
        _last_err = err;

        D = _d * deriv;
    }

    float out = P + I + D;

#ifdef DEBUG_PID
    Serial.print("  P: ");
    Serial.print(P);
    Serial.print("  I: ");
    Serial.print(I);
    Serial.print("  D: ");
    Serial.print(D);
    Serial.print("  Sum: ");
    Serial.println(out);
#endif

    return out;
}