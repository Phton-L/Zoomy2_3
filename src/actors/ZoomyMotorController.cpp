/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef Zoomy_MOTOR_Controller_CPP    
#define Zoomy_MOTOR_Controller_CPP

#include <Arduino.h>
#include "../../lib/ZoomyMotorController.h"
#include "../config/config.h"


ZoomyMotorController::ZoomyMotorController()
{
    this->_BarlowAllowedBackward = false;
    this->_BarlowAllowedForward = false;

    this->_camAllowedBackward = false;
    this->_camAllowedForward = false;

    this->_camDirection = true;
    this->_barlowDirection = true;
    this->_currentSpeed = 1000;
}

void ZoomyMotorController::begin(
            boolean camDirection, 
            boolean barlowDirection, 
            EndStop* ptrEndStopMiddel,
            EndStop* ptrEndStopCam,
            EndStop* ptrEndStopBarlow,
            MotorStepper* ptrStepperCam,
            MotorStepper* ptrStepperBarlow
            )
{
    this->_barlowDirection = barlowDirection;
    this->_camDirection = camDirection;
    this->_ptrEndStopBarlow = ptrEndStopBarlow;
    this->_ptrEndStopCam = ptrEndStopCam;
    this->_ptrEndStopMiddel = ptrEndStopMiddel;

    this->_ptrStepperBarlow = ptrStepperBarlow;
    this->_ptrStepperCam = ptrStepperCam;
    Serial.begin(9600);
}
boolean ZoomyMotorController::controlEndStop()
{
    this-> _BarlowAllowedBackward = !this->_ptrEndStopBarlow->getState();

    this-> _camAllowedBackward = !this-> _ptrEndStopCam->getState();

    this-> _camAllowedForward = !this-> _ptrEndStopMiddel->getState();
    this-> _BarlowAllowedForward = !this-> _ptrEndStopMiddel->getState(); // false wen in die richtung gefahren werden darf

    if (!this->_camAllowedBackward || !this->_camAllowedForward ||
        !this->_BarlowAllowedBackward || !this->_BarlowAllowedForward
        )
        return false;
    else
        return true;        
}
void ZoomyMotorController::calibration()
{
    while (!this->_ptrEndStopBarlow->getState() || !this->_ptrEndStopCam->getState())
    {
        Serial.print(!this->_ptrEndStopBarlow->getState());
        Serial.println("EndStopBarlow");
        while (!this->_ptrEndStopBarlow->getState())
            this->_ptrStepperBarlow->step(false,motorStepperStepDelayMicroSeconds); // bei true nach ausen fahren
        while(!this->_ptrEndStopCam->getState())
            this->_ptrStepperCam->step(false,motorStepperStepDelayMicroSeconds);
    }
    while (this->_ptrEndStopBarlow->getState() || this->_ptrEndStopCam->getState())
    {   
        while (this->_ptrEndStopBarlow->getState())
            this->_ptrStepperBarlow->step(true,motorStepperStepDelayMicroSeconds); // bei false in die mitte fahren
        while (this->_ptrEndStopCam->getState())
            this->_ptrStepperCam->step(true,motorStepperStepDelayMicroSeconds);
    }
    while (!this->_ptrEndStopBarlow->getState() || !this->_ptrEndStopCam->getState())
    {
        while (!this->_ptrEndStopBarlow->getState())
        {
            delayMicroseconds(motorStepperStepDelayMicroSeconds);
            this->_ptrStepperBarlow->step(false,motorStepperStepDelayMicroSeconds); // bei true nach ausen fahren
        }
        
        while (!this->_ptrEndStopCam->getState())
        {
            delayMicroseconds(motorStepperStepDelayMicroSeconds);
            this->_ptrStepperCam->step(false,motorStepperStepDelayMicroSeconds);
        }
    }
    this->_ptrStepperBarlow->setPosition(0);
    this->_ptrStepperCam->setPosition(0);
}
void ZoomyMotorController::stepCam(boolean direction,int speed)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperCam->step(direction,speed);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperCam->step(direction,speed);
}
void ZoomyMotorController::stepBarlow(boolean direction,int speed)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperBarlow->step(direction,speed);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperBarlow->step(direction,speed);
}
int ZoomyMotorController::currentSpeedReturn()
{
    return this->_currentSpeed;
}
void ZoomyMotorController::driveCam(int steps,boolean direction)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperCam->drive(steps,direction);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperCam->drive(steps,direction);
}
void ZoomyMotorController::driveBarlow(int steps,boolean direction)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperBarlow->drive(steps,direction);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperBarlow->drive(steps,direction);
}
/*
void ZoomyMotorController::stepCam(boolean direction,int speed)
{   
    this->controlEndStop();
    if (!direction && this->_camAllowedBackward)
       this->_ptrStepperCam->step(direction);
    if (direction && this->_camAllowedForward)
        this->_ptrStepperCam->step(direction);
}
void ZoomyMotorController::stepBarlow(boolean direction,int speed)
{   
    this->controlEndStop();
    if (direction && this->_BarlowAllowedForward)
       this->_ptrStepperBarlow->step(direction);
    if (!direction && this->_BarlowAllowedBackward)
        this->_ptrStepperBarlow->step(direction);
}
*/

#endif