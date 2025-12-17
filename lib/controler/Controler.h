/*
created by: Vinzent Schillinger
date: 01.11.2025
*/

#ifndef CONTROLER_H    
#define CONTROLER_H

#include <Arduino.h>
#include "../../lib/actors/MotorStepper.h"
#include "../../lib/sensor/Endstop.h"
class Controler
{
    private:
        MotorStepper* _controllerMotor;
        Endstop* _controllerEndSopEnd;
        Endstop* _controllerEndStopMiddel;

        int _controllerMultiplicatorSteps;

        long _distanceMM;

    public:

    Controler();

    void begin(MotorStepper* controllerMotor,
                Endstop* controllerEndSopEnd,
                Endstop* controllerEndStopMiddel,
                int controllerMultiplicatorSteps
                );
    
    long getDistanceMM();

    void drive();

    


};


#endif