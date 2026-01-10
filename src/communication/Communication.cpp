/*
created by: Vinzent Schillinger
date: 19.12.2015
*/
#ifndef COMMUNICATION_CPP
#define COMMUNICATION_CPP

#include "../../lib/communication/Communication.h"

Communication::Communication()
{

}
void Communication::begin(byte start,byte end,int bout,boolean serial1Bol)
{
    _serial1Bol = serial1Bol;
    _bout = bout;
    _start = start;
    _end = end;


    if(serial1Bol)
    {
        Serial1.begin(bout);
    }
    if(!serial1Bol)
    {
        Serial.begin(bout);
    }

}



void Communication::read(int &directionSend,int &speedSend)
{/*
   if(_serial1Bol)
    {
        if(Serial1.available())
        {
            if( Serial1.readBytes() == _start)
            {
                //byte fistInformazion = Serial1.readBytes();
                //byte secendInformaion = Serial1.readBytes();
            } 
        }
    }
        */ 
}
void Communication::send(int directionSend,int speedSend)
{
    
}
#endif