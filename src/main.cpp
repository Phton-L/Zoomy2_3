#include <Arduino.h>
#include "../config/config.h"
#include "../pins/pinsMain.h"
#include "../lib/actors/MotorStepper.h"
#include "../lib/sensor/EndStop.h"
#include "../lib/ZoomyMotorController.h"

long motorBarlowPositionReal = 0L;
long motorBarlowPositionTarget = 0L;

int speedStandard = 100;
int lastInput = 0;
//Motor prototype
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
  Serial.println("calibrate");
  //ZoomyController.calibration();
  
  
}

void loop() {
  //Communication
  //Increase Target
  //Decrease Targe
  //Stop -> Target = Real
  //Goto
  //Homing
  //Engine Control
if (Serial.available() > 0) {
      // 1. Read the byte into a variable so it can be checked multiple times
      Serial.print("available: ");
      int command = Serial.read();
      Serial.println(command);
      switch (command)
      {
        case 97:
          ZoomyController.driveCam(speedStandard,true);
          /*
          for (size_t i = 0; i < speedStandard; i++) 
          {
            //StepperCam.step(true);
            ZoomyController.stepCam(true,motorStepperStepDelayMicroSeconds);           
          }
           code */

          break;
        case 100:
          /*
            for (size_t i = 0; i < speedStandard; i++) 
          {
            //StepperCam.step(true);
            ZoomyController.stepCam(false,motorStepperStepDelayMicroSeconds);           
          }
            */
          ZoomyController.driveCam(speedStandard,false);

          break;
        case 119:
          /*
          for (size_t i = 0; i < speedStandard; i++) 
          {            
            ZoomyController.stepBarlow(true,motorStepperStepDelayMicroSeconds);          
          }
            */
          ZoomyController.driveBarlow(speedStandard,true);
          break;
        case 115:
          /*
          for (size_t i = 0; i < speedStandard; i++) 
          {            
            ZoomyController.stepBarlow(false,motorStepperStepDelayMicroSeconds);            
          }
            */
           ZoomyController.driveBarlow(speedStandard,false);
          break;
        case 49:
          Serial.println("Action 1 triggered 3200");
          speedStandard = 3200; 
          break;
        case 50:
          Serial.println("Action 2 triggered 1600");
          speedStandard = 3200/2;
          break;
        case 51:
          Serial.println("Action 3 triggered 1066");
          speedStandard = 3200/3;
          break;
        case 52:
          Serial.println("Action 4 triggered 800");
          speedStandard = 3200/4;
          break;
        case 53:
          Serial.println("Action 5 triggered 640");
          speedStandard = 3200/5;
          break;
        case 54:
          Serial.println("Action 6 triggered 533");
          speedStandard = 3200/6;
          break;
        case 55:
          Serial.println("Action 7 triggered 457");
          speedStandard = 3200/7;
          break;
        case 56:
          Serial.println("Action 8 triggered 400");
          speedStandard = 3200/8;
          break;
        case 57:
          Serial.println("Action 9 triggered 355");
          speedStandard = 3200/9;
          break;
        case 48:
          Serial.println("Action 10 triggered 320");
          speedStandard = 3200/10;
          break;
        default:
          break;
      }
    while (Serial.available())
          {
            Serial.read();
          }
      
    //Examining boundary conditions
    
      //if (EndStoppBarlow.getState() || EndStoppMiddel.getState())
    //StepperBarlow.step(true)
    
  }
}
// formula
// L1=(53.8(zoom factor)-62.2 I don't think the information given in mm is correct.
//  L = 4,8 *Zoom faktor  -2