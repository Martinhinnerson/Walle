/*
 * timer.h
 * 
 * A timer class used to handle function calls with set delays
 * 
 * There is currently a big problem with this class.
 * Right now the callback function has to be static which means that 
 * if it is not global (which it should not be) the callback function cannot use any
 * private member variable or functions (which most of them do...).alignas
 * 
 * One solution to this is to implement boost:: which allows non-static member functions
 * in a callback.
 *  
 */

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// Max number of timers allowed
#define MAX_TIMERS 5

//type definition of the callback function so that it can be sent in the setTimer function
typedef void (*callback_function)();

class Timer
{

  private:
    //delay values for the timers
    unsigned long _delays[MAX_TIMERS];
    //previous millis() value. Used to calculate the delay
    unsigned long _prev_millis[MAX_TIMERS];
    //If the timer is enabled
    boolean _enabled[MAX_TIMERS];
    //Function to run when the timer had reached its delay
    callback_function _callbacks[MAX_TIMERS];
    //number of timers used
    int _numTimers;

  public:
    //Constructor
    Timer();
    //function to call in the main loop
    void run();
    //set a timer "id" to run ever d milliseconds and call function f after every delay
    void setTimer(unsigned long d, callback_function f, int id);
    //check if timer "id" is enabled
    boolean isEnabled(int id);
    //enable timer "id"
    void enable(int id);
    //diabled timer "id"
    void disable(int id);
    //toggle timer "id"
    void toggle(int id);
};

#endif