/*
created by: Vinzent Schillinger
date: 26.10.2025
*/

#ifndef CONFIG_H
#define CONFIG_H

#define motorBarlowDirection false
#define motorStepperStepDelayMicroSeconds 80
#define motorCamDirection true
#define ControllerMotorMultiplicationFactor 0.5

#define motorStepperStepDelayMicroSecondsMax 700

#define accelerationSteps 620 //How many steps does the acceleration take?

// one revolution = 3200 steps

#define endStopPullup true
#define endStopInvert true


#endif