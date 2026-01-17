/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef Zoomy_MOTOR_Controller_H
#define Zoomy_MOTOR_Controller_H

#include <Arduino.h>
#include "actors/MotorStepper.h"
#include "sensor/EndStop.h"


class ZoomyMotorController
{
    private:

        EndStop* _ptrEndStopMiddel;
        EndStop* _ptrEndStopCam;
        EndStop* _ptrEndStopBarlow;

        MotorStepper* _ptrStepperCam;
        MotorStepper* _ptrStepperBarlow;

        boolean _camAllowedForward;
        boolean _camAllowedBackward;

        boolean _BarlowAllowedForward;
        boolean _BarlowAllowedBackward;

        boolean _camDirection;
        boolean _barlowDirection;
        int _currentSpeed;
    
    public:
        ZoomyMotorController();
        void begin(
            boolean camDirection, 
            boolean barlowDirection, 
            EndStop* ptrEndStopMiddel,
            EndStop* ptrEndStopCam,
            EndStop* ptrEndStopBar,
            MotorStepper* ptrStepperCam,
            MotorStepper* ptrStepperBarlow
            );

        boolean controlEndStop(); // only EndStops

        void calibration();

        void stepCam(boolean direction,int speed);

        void stepBarlow(boolean direction,int speed);

        int currentSpeedReturn();

        void driveCam(int steps,boolean direction);

        void driveBarlow(int steps,boolean direction);

        void ubDateCam();


};
#endif