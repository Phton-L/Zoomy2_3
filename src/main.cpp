#include <Arduino.h>
#include "../config/config.h"
#include "../pins/pinsMain.h"
#include "../lib/actors/MotorStepper.h"
#include "../lib/sensor/EndStop.h"
#include "../lib/ZoomyMotorController.h"

long motorBarlowPositionReal = 0L;
long motorBarlowPositionTarget = 0L;

int speedStandart = 100;
int lastInput = 0;
//Motor Prototyp
MotorStepper StepperCam = MotorStepper();
MotorStepper StepperBarlow = MotorStepper();


// EndStop
EndStop EndStoppCam = EndStop();
EndStop EndStoppBarlow = EndStop();
EndStop EndStoppMiddle = EndStop();
//
ZoomyMotorController ZoomyController = ZoomyMotorController();

void setup() {
  Serial.begin(9600);
  StepperBarlow.begin(pinMotorBarlowEna, pinMotorBarlowStp, pinMotorBarlowDir, directionBarlow);
  StepperCam.begin(pinMotorCamEna, pinMotorCamStp, pinMotorCamDir, directionCam);
  // endStop
  EndStoppBarlow.begin(pinEndStopBarlow, endStopInvert, endStopPullup);
  EndStoppCam.begin(pinEndStopCam, endStopInvert, endStopPullup);
  EndStoppMiddle.begin(pinEndStopMiddel, endStopInvert, endStopPullup);

  ZoomyController.begin(motorCamDirection,motorBarlowDirection,&EndStoppMiddle,&EndStoppCam,&EndStoppBarlow,&StepperCam, &StepperBarlow);
  Serial.println("calibracen");
  //ZoomyController.calibration();
  
  
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
          ZoomyController.driveCam(speedStandart,true);
          /*
          for (size_t i = 0; i < speedStandart; i++) 
          {
            //StepperCam.step(true);
            ZoomyController.stepCam(true,motorStepperStepDelayMicroSeconds);           
          }
           code */

          break;
        case 100:
          /*
            for (size_t i = 0; i < speedStandart; i++) 
          {
            //StepperCam.step(true);
            ZoomyController.stepCam(false,motorStepperStepDelayMicroSeconds);           
          }
            */
          ZoomyController.driveCam(speedStandart,false);

          break;
        case 119:
          /*
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            ZoomyController.stepBarlow(true,motorStepperStepDelayMicroSeconds);          
          }
            */
          ZoomyController.driveBarlow(speedStandart,true);
          break;
        case 115:
          /*
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            ZoomyController.stepBarlow(false,motorStepperStepDelayMicroSeconds);            
          }
            */
           ZoomyController.driveBarlow(speedStandart,false);
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
        case 55:
          Serial.println("Action 7 triggered 457");
          speedStandart = 3200/7;
          break;
        case 56:
          Serial.println("Action 8 triggered 400");
          speedStandart = 3200/8;
          break;
        case 57:
          Serial.println("Action 9 triggered 355");
          speedStandart = 3200/9;
          break;
        case 48:
          Serial.println("Action 10 triggered 320");
          speedStandart = 3200/10;
          break;
        default:
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