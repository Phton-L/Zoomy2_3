/*
created by: Vinzent Schillinger
date: 01.11.2025
*/

#ifndef CONTROLER_CPP    
#define CONTROLER_CPP

#include <Arduino.h>
#include "../../lib/controler/Controler.h"


Controler::Controler()
{
}
void Controler::begin(MotorStepper* controllerMotor,
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
long Controler::getDistanceMM()
{
    _distanceMM = this->_controllerMotor->getPosition()*_controllerMultiplicatorSteps;
    return _distanceMM;
}

#endif