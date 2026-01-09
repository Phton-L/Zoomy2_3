#include <Arduino.h>
#include "../config/config.h"
#include "../pins/pinsMain.h"
#include "../lib/actors/MotorStepper.h"
#include "../lib/sensor/EndStop.h"
#include "../lib/zoomyMotorContoller.h"

long motorBarlowPositionReal = 0L;
long motorBarlowPositionTarget = 0L;

int speedStandart = 100;
int lastInput = 0;
//Motor Prototyp
MotorStepper StepperCam = MotorStepper();
MotorStepper StepperBarlow = MotorStepper();


// EndStop
EndStop EndStoppCam = Endstop();
EndStop EndStoppBarlow = Endstop();
EndStop EndStoppMiddle = Endstop();
//
SoomyMotorContoller SoomyContoller = SoomyMotorContoller();

void setup() {
  Serial.begin(9600);
  StepperBarlow.begin(pinMotorBarlowEna, pinMotorBarlowStp, pinMotorBarlowDir, directionBarlow);
  StepperCam.begin(pinMotorCamEna, pinMotorCamStp, pinMotorCamDir, directionCam);
  // endStop
  EndStoppBarlow.begin(pinEndStopBarlow, endStopInvert, endStopPullup);
  EndStoppCam.begin(pinEndStopCam, endStopInvert, endStopPullup);
  EndStoppMiddle.begin(pinEndStopMiddel, endStopInvert, endStopPullup);

  SoomyContoller.begin(motorCamDirection,motorBarlowDirection,&EndStoppMiddle,&EndStoppCam,&EndStoppBarlow,&StepperCam, &StepperBarlow);
  Serial.println("calibracen");
  SoomyContoller.calibration();
  
}

void loop() {
  //Communication
    //Erhöhe Target
    //Verringere Target
    //Stop -> Target = Real
    //Goto
    //Homing
  //Motorregelung
if (Serial.available() > 0) {
      // 1. Read the byte into a variable so it can be checked multiple times
      Serial.print("availbel: ");
      int command = Serial.read();
      Serial.println(command);
      switch (command)
      {
        case 97:
          Serial.println("Action 1 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {
            //StepperCam.step(true);
            SoomyController.stepCam(true,motorStepperStepDelayMicroSecons);           
          }
          /* code */
          break;
        case 100:           
            SoomyController.stepCam(false,motorStepperStepDelayMicroSecons);
            lastInput = 100;

          break;
        case 119:
          Serial.println("Action 3 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            SoomyController.stepBarlow(true,motorStepperStepDelayMicroSecons);          
          }
          break;
        case 115:
          Serial.println("Action 4 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            SoomyController.stepBarlow(false,motorStepperStepDelayMicroSecons);            
          }
          break;
        case 49:
          Serial.println("Action 1 triggered 3200");
          speedStandart = 3200; // volle 
          break;
        case 50:
          Serial.println("Action 2 triggered 1600");
          speedStandart = 3200/2;
          break;
        case 51:
          Serial.println("Action 3 triggered 1066");
          speedStandart = 3200/3;
          break;
        case 52:
          Serial.println("Action 4 triggered 800");
          speedStandart = 3200/4;
          break;
        case 53:
          Serial.println("Action 5 triggered 640");
          speedStandart = 3200/5;
          break;
        case 54:
          Serial.println("Action 6 triggered 533");
          speedStandart = 3200/6;
          break;
        default:
          switch (lastInput)
          {
          case 100:
            while (SoomyController.currentSpeedReturn() > 0)
            {
              SoomyController.stepCam(false,0);
            }
            break;
          
          default:
            break;
          }
          break;
      }
    while (Serial.available())
          {
            Serial.read();
          }
      
    //Randbedingungn prüfend
    
      //if (EndStoppBarlow.getState() || EndStoppMiddel.getState())
    //StepperBarlow.step(true)
    
  }
}
// formel
// L1=(53.8(soom faktor)-62.2 die angeben in mm stimmt glaube nicht
//  L = 4,8 *Soomfaktor  -2