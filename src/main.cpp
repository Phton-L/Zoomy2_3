#include <Arduino.h>
#include "../config/config.h"
#include "../pins/pinsMain.h"
#include "../lib/actors/MotorStepper.h"
#include "../lib/sensor/Endstop.h"
#include "../lib/SoomyMotorContoler.h"

long motorBarlowPositionReal = 0L;
long motorBarlowPositionTarget = 0L;

//Motor Prototyp
MotorStepper StepperCam = MotorStepper();
MotorStepper StepperBarlow = MotorStepper();


// EndStop
Endstop EndStoppCam = Endstop();
Endstop EndStoppBarlow = Endstop();
Endstop EndStoppMiddle = Endstop();
//
SoomyMotorContoler SoomyContoler = SoomyMotorContoler();

void setup() {
  Serial.begin(9600);
  StepperBarlow.begin(pinMotorBarlowEna, pinMotorBarlowStp, pinMotorBarlowDir, directionBarlow);
  StepperCam.begin(pinMotorCamEna, pinMotorCamStp, pinMotorCamDir, directionCam);
  // endStop
  EndStoppBarlow.begin(pinEndStopBarlow, endStopInvert, endStopPullup);
  EndStoppCam.begin(pinEndStopCam, endStopInvert, endStopPullup);
  EndStoppMiddle.begin(pinEndStopMiddel, endStopInvert, endStopPullup);

  SoomyContoler.begin(motorCamDirection,motorBarlowDirection,&EndStoppMiddle,&EndStoppCam,&EndStoppBarlow,&StepperCam, &StepperBarlow);
  Serial.println("calibracen");
  SoomyContoler.calibracen();
}

void loop() {
  //Communikation
    //Erhöhe Target
    //Verringere Target
    //Stop -> Target = Real
    //Goto
    //Homing
  Serial.println("step");
  //Motorregelung

  //Randbedingungn prüfend
  
  Serial.println("step");
    //if (EndStoppBarlow.getState() || EndStoppMiddel.getState())
  //StepperBarlow.step(true);
  delay(10);
  
}