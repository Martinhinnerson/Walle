/*
 * timer.h
 * 
 * A timer class used to handle function calls with set delays
 *  
 */

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{

  private:
    //delay value for the timer
    unsigned long _delay;
    //previous millis() value. Used to calculate the delay
    unsigned long _prev_millis;
    //If the timer is enabled
    boolean _enabled;

  public:
    //Constructor
    Timer();
    //function to call in the main loop
    boolean check();
    //set a timerto run ever d milliseconds
    void setTimer(unsigned long d);
    //check if timer is enabled
    boolean isEnabled();
    //enable timer 
    void enable();
    //diabled timer
    void disable();
    //toggle timer
    void toggle();
};

#endif