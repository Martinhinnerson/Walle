#include "timer.h"

Timer::Timer()
{
    unsigned long current_millis = millis();
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        _enabled[i] = false;
        _callbacks[i] = 0;
        _prev_millis[i] = current_millis;
    }
    _numTimers = 0;
}


/*
 * run()
 * 
 * This function should be called in the main loop
 * 
 * The function checks each timer
 * If a timers delay has passed, this function updated the _prev_millis and
 * calls the callback_function
 * 
 * Inputs: none
 * Outputs: none
 * 
 */
void Timer::run()
{
    //get current time
    unsigned long current_millis = millis();

    //loop through the timers
    for (int i = 0; i < MAX_TIMERS; i++)
    {
        if (_enabled[i])
        {
            if (current_millis - _prev_millis[i] >= _delays[i])
            {
                _prev_millis[i] += _delays[i];
                _callbacks[i]();
            }
        }
    }
}

/*
 * setTimer()
 * 
 * This function is used to set a timer
 * 
 * Inputs: delay d, callback_function f, timer id
 * Outputs: boolean true if succeded, false otherwise
 * 
 */ 
boolean Timer::setTimer(unsigned long d, callback_function f, int id)
{

    if (id > MAX_TIMERS)
    {
        Serial.println("Error creating timer. Index bigger than max index.");
        return false;
    }

    _delays[id] = d;
    _enabled[id] = true;
    _prev_millis[id] = millis();
    _callbacks[id] = f;

    _numTimers++;

    return true;
}

boolean Timer::isEnabled(int id)
{
    return _enabled[id];
}
void Timer::enable(int id)
{
    _enabled[id] = true;
}
void Timer::disable(int id)
{
    _enabled[id] = false;
}
void Timer::toggle(int id)
{
    _enabled[id] = !_enabled[id];
}
