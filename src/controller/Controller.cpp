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
                EndStop* controllerEndSopEnd,
                EndStop* controllerEndStopMiddel,
                int MultiplicationFactor
                )
{
    this->_controllerMotor = controllerMotor;
    this->_controllerEndSopEnd = controllerEndSopEnd;
    this->_controllerEndStopMiddel = controllerEndStopMiddel;
    this->_controllerMultiplicationFactorSteps = MultiplicationFactor;
}
long Controller::getDistanceMM()
{
    _distanceMM = this->_controllerMotor->getPosition()*_controllerMultiplicationFactorSteps;
    return _distanceMM;
}

#endif