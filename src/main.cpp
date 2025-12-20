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
  //Motorregelung
if (Serial.available() > 0) {
    // 1. Read the byte into a variable so it can be checked multiple times
    char command = Serial.read();

    // 2. Check for '1'
    if (command == '1') {
      Serial.println("Action 1 triggered");
      for (size_t i = 0; i < 1000; i++) {
        
        StepperCam.step(true);
        
      }
    } 
    // 3. Check for '2' (Use 'else if' for efficiency)
    if (command == '2') {
      Serial.println("Action 2 triggered");
      for (size_t i = 0; i < 1000; i++) {
        
        StepperCam.step(false);
      }
    }
    if (command == '3') {
      Serial.println("Action 3 triggered");
      for (size_t i = 0; i < 1000; i++) {
        
        StepperBarlow.step(false);
      }
    }
    if (command == '4') {
      Serial.println("Action 4 triggered");
      for (size_t i = 0; i < 1000; i++) {
        
        StepperBarlow.step(true);
      }
    }
    delay(10);
    while (Serial.available())
    {
      Serial.read();
    }
    
  //Randbedingungn prüfend
  
    //if (EndStoppBarlow.getState() || EndStoppMiddel.getState())
  //StepperBarlow.step(true)
  
}
}