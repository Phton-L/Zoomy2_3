/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef MOTOR_STEPPER_H
#define MOTOR_STEPPER_H

#include <Arduino.h>

class MotorStepper
{
private:
    //Pins
    byte _pinEna;
    byte _pinStp;
    byte _pinDir;
    long lastTime;
    //Direction
    boolean _direction;

    //Position
    unsigned long _position; //Actual Position

public:
    //Startup
    MotorStepper();
    void begin(byte pinEna,
                byte pinStp,
                byte pinDir,
                boolean direction);
    
    //Setter
    void setPosition(unsigned long position);

    //Getter
    unsigned long getPosition();

    //Usage
    void step(boolean direction,int speed);
};

#endif