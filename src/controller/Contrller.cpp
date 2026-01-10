/*
created by: Vinzent Schillinger
date: 01.11.2025
*/

#ifndef CONTROLLER_CPP    
#define CONTROLLER_CPP

#include <Arduino.h>
#include "../../lib/controller/Controller.h"


Controller::Controller()
{
}
void Controller::begin(MotorStepper* controllerMotor,
                Endstop* controllerEndSopEnd,
                Endstop* controllerEndStopMiddel,
                int controllerMultiplicatorSteps
                )
{
    this->_controllerMotor = controllerMotor;
    this->_controllerEndSopEnd = controllerEndSopEnd;
    this->_controllerEndStopMiddel = controllerEndStopMiddel;
    _controllerMultiplicatorSteps = controllerMultiplicatorSteps;
}
long Controller::getDistanceMM()
{
    _distanceMM = this->_controllerMotor->getPosition()*_controllerMultiplicatorSteps;
    return _distanceMM;
}

#endif