#include <Arduino.h>
#include "../config/config.h"
#include "../pins/pinsMain.h"
#include "../lib/actors/MotorStepper.h"
#include "../lib/sensor/Endstop.h"
#include "../lib/SoomyMotorContoler.h"

long motorBarlowPositionReal = 0L;
long motorBarlowPositionTarget = 0L;

int speedStandart = 100;
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
      Serial.print("avaibel: ");
      int command = Serial.read();
      Serial.println(command);
      switch (command)
      {
        case 97:
          Serial.println("Action 1 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {
            //StepperCam.step(true);
            SoomyContoler.stepCam(true);           
          }
          /* code */
          break;
        case 100:
          Serial.println("Action 2 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {           
            SoomyContoler.stepCam(false);
          }
          break;
        case 119:
          Serial.println("Action 3 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            SoomyContoler.stepBarlow(true);          
          }
          break;
        case 115:
          Serial.println("Action 4 triggered");
          for (size_t i = 0; i < speedStandart; i++) 
          {            
            SoomyContoler.stepBarlow(false);            
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