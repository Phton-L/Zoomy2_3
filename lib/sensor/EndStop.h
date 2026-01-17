/*
created by: Vinzent Schillinger
date: 12.03.2024
*/

#ifndef ENDSTOP_H
#define ENDSTOP_H


#include <Arduino.h>

class EndStop
{
private:
    byte _pin;
    boolean _invert;

public:
    EndStop();
    void begin(byte pin, boolean invert, boolean pullUp);
    boolean getState();
};

#endif