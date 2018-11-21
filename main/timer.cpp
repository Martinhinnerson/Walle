#include "timer.h"

Timer::Timer()
{
    _enabled = false;
    _prev_millis = millis();
}


/*
 * run()
 * 
 * This function should be called in the main loop
 * 
 * Inputs: none
 * Outputs: true if the timer has passed, false otherwise
 * 
 */
boolean Timer::check()
{
    //get current time
    unsigned long current_millis = millis();

    if (_enabled)
    {
        if (current_millis - _prev_millis >= _delay)
        {
            _prev_millis += _delay;
            return true;
        }
    }
    return false;
}

/*
 * setTimer()
 * 
 * This function is used to set a timer
 * 
 * Inputs: delay d
 * Outputs: none
 * 
 */ 
void Timer::setTimer(unsigned long d)
{
    _delay = d;
    _enabled = true;
    _prev_millis = millis();
}

boolean Timer::isEnabled()
{
    return _enabled;
}
void Timer::enable()
{
    _enabled = true;
}
void Timer::disable()
{
    _enabled = false;
}
void Timer::toggle()
{
    _enabled = !_enabled;
}
