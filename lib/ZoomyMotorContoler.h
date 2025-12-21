/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef SOOMY_MOTOR_CONTOLER_H
#define SOOMY_MOTOR_CONTOLER_H

#include <Arduino.h>
#include "actors/MotorStepper.h"
#include "sensor/Endstop.h"

class SoomyMotorContoler
{
    private:

        Endstop* _ptrEndstopEndStopMiddel;
        Endstop* _ptrEndstopEndStopCam;
        Endstop* _ptrEndstopEndStopBarlow;

        MotorStepper* _ptrStepperCam;
        MotorStepper* _ptrStepperBarlow;

        boolean _camAllowedForward;
        boolean _camAllowedBackward;

        boolean _BarlowAllowedForward;
        boolean _BarlowAllowedBackward;

        boolean _camDirection;
        boolean _barlowDirection;
    public:
    
    public:
        SoomyMotorContoler();
        void begin(
            boolean camDirection, 
            boolean barlowDirection, 
            Endstop* ptrEndstopEndStopMiddel,
            Endstop* ptrEndstopEndStopCam,
            Endstop* ptrEndstopEndStopBar,
            MotorStepper* ptrStepperCam,
            MotorStepper* ptrStepperBarlow
            );

        boolean controlEndStop(); // only Endstops

        void camDrive(
                int camDriveSpeed, 
                byte camDriveSteppes, 
                boolean camDriveDirection
                );

        void calibracen();

        void stepCam(boolean direction);

        void stepBarlow(boolean direction);

};
#endif