/*
created by: Markus Kohler
date: 12.033.2024
*/

#ifndef ENDSTOP_CPP
#define ENDSTOP_CPP

#include <Arduino.h>
#include "../../config/config.h"
#include "../../lib/sensor/Endstop.h"

Endstop::Endstop()
{
    this->_pin = 0;
    this->_invert = false;
}

void Endstop::begin(byte pin, boolean invert, boolean pullup)
{
    this->_pin = pin;
    this->_invert = invert;

    if(pullup)
    {
        pinMode(this->_pin, INPUT_PULLUP);
    }
    else
    {
        pinMode(this->_pin, INPUT);
    }
}

boolean Endstop::getState()
{
    if(this->_invert)
    {
        return !digitalRead(this->_pin);
    }
    return digitalRead(this->_pin);
}

#endif