/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef SOOMY_MOTOR_CONTOLER_CPP    
#define SOOMY_MOTOR_CONTOLER_CPP

#include <Arduino.h>
#include "../../lib/SoomyMotorContoler.h"
#include "../config/config.h"


SoomyMotorContoler::SoomyMotorContoler()
{
    this->_BarlowAllowedBackward = false;
    this->_BarlowAllowedForward = false;

    this->_camAllowedBackward = false;
    this->_camAllowedForward = false;

    this->_camDirection = true;
    this->_barlowDirection = true;
}

void SoomyMotorContoler::begin(
            boolean camDirection, 
            boolean barlowDirection, 
            Endstop* ptrEndstopEndStopMiddel,
            Endstop* ptrEndstopEndStopCam,
            Endstop* ptrEndstopEndStopBarlow,
            MotorStepper* ptrStepperCam,
            MotorStepper* ptrStepperBarlow
            )
{
    this->_barlowDirection = barlowDirection;
    this->_camDirection = camDirection;
    this->_ptrEndstopEndStopBarlow = ptrEndstopEndStopBarlow;
    this->_ptrEndstopEndStopCam = ptrEndstopEndStopCam;
    this->_ptrEndstopEndStopMiddel = ptrEndstopEndStopMiddel;

    this->_ptrStepperBarlow = ptrStepperBarlow;
    this->_ptrStepperCam = ptrStepperCam;
    Serial.begin(9600);
}
boolean SoomyMotorContoler::controlEndStop()
{
    this-> _BarlowAllowedBackward = !this->_ptrEndstopEndStopBarlow->getState();

    this-> _camAllowedBackward = !this-> _ptrEndstopEndStopCam->getState();

    this-> _camAllowedForward = !this-> _ptrEndstopEndStopMiddel->getState();
    this-> _BarlowAllowedForward = !this-> _ptrEndstopEndStopMiddel->getState(); // false wen in die richtung gefahren werden darf

    if (!this->_camAllowedBackward || !this->_camAllowedForward ||
        !this->_BarlowAllowedBackward || !this->_BarlowAllowedForward
        )
        return false;
    else
        return true;        
}
void SoomyMotorContoler::calibracen()
{
    while (!this->_ptrEndstopEndStopBarlow->getState() || !this->_ptrEndstopEndStopCam->getState())
    {
        Serial.print(!this->_ptrEndstopEndStopBarlow->getState());
        Serial.println("EndstopBarlow");
        while (!this->_ptrEndstopEndStopBarlow->getState())
            this->_ptrStepperBarlow->step(false); // bei true nach ausen fahren
        while(!this->_ptrEndstopEndStopCam->getState())
            this->_ptrStepperCam->step(false);
    }
    while (this->_ptrEndstopEndStopBarlow->getState() || this->_ptrEndstopEndStopCam->getState())
    {   
        while (this->_ptrEndstopEndStopBarlow->getState())
            this->_ptrStepperBarlow->step(true); // bei false in die mitte fahren
        while (this->_ptrEndstopEndStopCam->getState())
            this->_ptrStepperCam->step(true);
    }
    while (!this->_ptrEndstopEndStopBarlow->getState() || !this->_ptrEndstopEndStopCam->getState())
    {
        while (!this->_ptrEndstopEndStopBarlow->getState())
        {
            delayMicroseconds(motorStepperStepDelayMicroSecons);
            this->_ptrStepperBarlow->step(false); // bei true nach ausen fahren
        }
        
        while (!this->_ptrEndstopEndStopCam->getState())
        {
            delayMicroseconds(motorStepperStepDelayMicroSecons);
            this->_ptrStepperCam->step(false);
        }
    }
    this->_ptrStepperBarlow->setPosition(0);
    this->_ptrStepperCam->setPosition(0);
}
void SoomyMotorContoler::stepCam(boolean direction)
{   
    this->controlEndStop();
    if (!direction && this->_camAllowedBackward)
       this->_ptrStepperCam->step(direction);
    if (direction && this->_camAllowedForward)
        this->_ptrStepperCam->step(direction);
}
void SoomyMotorContoler::stepBarlow(boolean direction)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperBarlow->step(direction);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperBarlow->step(direction);
}
#endif