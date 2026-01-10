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
    this->lastTime = millis();

    //initialize Ports
    pinMode(this->_pinEna, OUTPUT);
    pinMode(this->_pinStp, OUTPUT);
    pinMode(this->_pinDir, OUTPUT);

    digitalWrite(this->_pinEna, LOW);
    digitalWrite(this->_pinStp, LOW);
    digitalWrite(this->_pinDir, LOW);
}

//Set
void MotorStepper::setPosition(unsigned long position)
{
    this->_position = position;
}

//Get
unsigned long MotorStepper::getPosition()
{
    return this->_position;
}

//Step
void MotorStepper::step(boolean direction,int speed)
{
    digitalWrite(this->_pinDir, (this->_direction == direction)); // bei true nach ausen fahren bei false in die mitte
    digitalWrite(this->_pinStp, HIGH);
    delayMicroseconds(speed);
    digitalWrite(this->_pinStp, LOW);
    delayMicroseconds(speed);
    this->lastTime = millis();
    if(direction)
    {
        this->_position++;
    }
    else
    {
        this->_position--;
    }
}
void MotorStepper::drive(int steps,bool foreard)
{
    digitalWrite(this->_pinDir, (this->_direction == foreard)); // bei true nach ausen fahren bei false in die mitte
    int currentDelay = motorStepperStepDelayMicroSeconsMax;
    int delayStep =(motorStepperStepDelayMicroSeconsMax -motorStepperStepDelayMicroSecons) / accelerationSteps;

    for(int i=0; i< steps; i++)
    {
        
    digitalWrite(this->_pinStp, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_pinStp, LOW);
    delayMicroseconds(currentDelay);

    if (i < accelerationSteps) {
      currentDelay -= delayStep;
    }
    // 2. Bremsphase (Am Ende)
    else if (i > (steps - accelerationSteps)) {
      currentDelay += delayStep;
    }
    
    // Sicherheit: Delay nicht unter minDelay fallen lassen
    if (currentDelay < motorStepperStepDelayMicroSecons) currentDelay = motorStepperStepDelayMicroSecons;
    }
}

#endif