/*
created by: Vinzent Schillinger
date: 01.11.2025
*/

#ifndef CONTROLLER_H    
#define CONTROLLER_H

#include <Arduino.h>
#include "../../lib/actors/MotorStepper.h"
#include "../../lib/sensor/EndStop.h"
class Controller
{
    private:
        MotorStepper* _controllerMotor;
        EndStop* _controllerEndSopEnd;
        EndStop* _controllerEndStopMiddel;

        int _controllerMultiplicationFactorSteps;

        long _distanceMM;

    public:

    Controller();

    void begin(MotorStepper* controllerMotor,
                EndStop* controllerEndSopEnd,
                EndStop* controllerEndStopMiddel,
                int MultiplicationFactor
                );
    
    long getDistanceMM();

    void drive();

    


};


#endif