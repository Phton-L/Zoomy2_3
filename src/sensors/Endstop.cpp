/*
created by: Markus Kohler
date: 12.033.2024
*/

#ifndef END_STOP_CPP
#define END_STOP_CPP

#include <Arduino.h>
#include "../../config/config.h"
#include "../../lib/sensor/EndStop.h"

EndStop::EndStop()
{
    this->_pin = 0;
    this->_invert = false;
}

void EndStop::begin(byte pin, boolean invert, boolean pullUp)
{
    this->_pin = pin;
    this->_invert = invert;

    if(pullUp)
    {
        pinMode(this->_pin, INPUT_PULLUP);
    }
    else
    {
        pinMode(this->_pin, INPUT);
    }
}

boolean EndStop::getState()
{
    if(this->_invert)
    {
        return !digitalRead(this->_pin);
    }
    return digitalRead(this->_pin);
}

#endif