/*
created by: Vinzent Schillinger
date: 01.11.2025
*/

#ifndef CONTROLER_H    
#define CONTROLER_H

#include <Arduino.h>
#include "../../lib/actors/MotorStepper.h"
#include "../../lib/sensor/EndStop.h"
class Controller
{
    private:
        MotorStepper* _controllerMotor;
        EndStop* _controllerEndSopEnd;
        EndStop* _controllerEndStopMiddel;

        int _controllerMultiplicatorSteps;

        long _distanceMM;

    public:

    Controller();

    void begin(MotorStepper* controllerMotor,
                Endstop* controllerEndSopEnd,
                Endstop* controllerEndStopMiddel,
                int controllerMultiplicatorSteps
                );
    
    long getDistanceMM();

    void drive();

    


};


#endif