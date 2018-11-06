#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>

class Radio
{
    int _joystick_x;
    int _joystick_y;
    int _joystick_rot;

  public:
    Radio();
    void setJoysticInputs(int x, int y);
    int getJoysticX();
    int getJoysticY();
    void updateRadio();
    void test_cppm();
};

#endif
