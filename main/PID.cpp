#include "PID.h"
#include <Arduino.h>

PID::PID()
{
    // Simple initiatlisation of PID
    clear();
}

PID::PID(float kp, float ki, float kd)
{
    setCoefficients(kp, ki, kd);
}

void PID::clear()
{
    _Kp = 0;
    _Ki = 0;
    _Kd = 0;
    _err_k_1 = 0; 
    _err_k_2 = 0;
    _cfg_err = false;
}

bool PID::setCoefficients(float Kp, float Ki, float Kd)
{
    _Kp = Kp;
    _Ki = Ki;
    _Kd = Kd;
    return !_cfg_err;
}

void PID::setCfgErr()
{
    _cfg_err = true;
    _Kp = _Ki = _Kd = 0;
}

//Error that can be set if something is wrong
//This is for set if something is wrong in the setup
bool PID::err()
{
    return _cfg_err;
}

/* Calculate control signal to determine should implement PID controller on velocity form:
    u_k = u_{k-1} + Kp*(e_k - e_{k-1}) + Ki*e_k + Kd*(e_k + 2*e_{k-1} + e_{k-1})
    This means that the sum of previous errors doesn't have to be maintained, removing any problem of 
    a potential overflow (which should really happen anyway). */
float PID::calculate(float sp, float fb)
{

    float err = sp - fb; //This should be modified for certain behaviour, eg. wraparoud
    float P = 0, I = 0, D = 0;

    MOD(err); //The modulo function defined in PID.h wraps around the value because
    //we always want to rotate the closest direction

    if (_Kp)
    {
        P = _Kp * (err - _err_k_1);
    }

    if (_Ki)
    {
        I = _Ki * err;
    }

    if (_Kd)
    {
        D = _Kd * (err + 2 * _err_k_1 + _err_k_2);
    }

    _err_k_1 = err;
    _err_k_2 = _err_k_1;
    
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