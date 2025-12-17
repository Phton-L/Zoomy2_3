/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef MOTOR_STEPPER_CPP
#define MOTOR_STEPPER_CPP

#include <Arduino.h>
#include "../../lib/actors/MotorStepper.h"
#include "../../config/config.h"

MotorStepper::MotorStepper()
{
    this->_pinEna = 0;
    this->_pinStp = 0;
    this->_pinDir = 0;
    this->_direction = false;
}

void MotorStepper::begin(
                byte pinEna,
                byte pinStp,
                byte pinDir,
                boolean direction)
{
    //set variables
    this->_pinEna = pinEna;
    this->_pinStp = pinStp;
    this->_pinDir = pinDir;
    this->_direction = direction;

    //initialise Ports
    pinMode(this->_pinEna, OUTPUT);
    pinMode(this->_pinStp, OUTPUT);
    pinMode(this->_pinDir, OUTPUT);

    digitalWrite(this->_pinEna, LOW);
    digitalWrite(this->_pinStp, LOW);
    digitalWrite(this->_pinDir, LOW);
}

//Setter
void MotorStepper::setPosition(unsigned long position)
{
    this->_position = position;
}

//Getter
unsigned long MotorStepper::getPosition()
{
    return this->_position;
}

//Usage
void MotorStepper::step(boolean direction)
{
    digitalWrite(this->_pinDir, (this->_direction == direction)); // bei true nach ausen fahren bei false in die mitte
    digitalWrite(this->_pinStp, HIGH);
    delayMicroseconds(motorStepperStepDelayMicroSecons);
    digitalWrite(this->_pinStp, LOW);
    delayMicroseconds(motorStepperStepDelayMicroSecons);
    if(direction)
        this->_position++;
    else
        this->_position--;
}

#endif