/*
created by: Vinzent Schillinger
date: 19.12.2015
*/

#ifndef COMMINICATION_CPP
#define COMMINICATION_CPP

#include "../../lib/cominication/Comminication.h"

Comminication::Comminication()
{

}
Comminication::begin(byte start,byte end,int bout,boolean serial1Bol)
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



Comminication::read()
{
   if(_serial1Bol)
    {
        if(Serial1.available())
        {
            if( Serial1.readBytes() == _start)
            {
                byte fistInformazion = Serial1.readBytes();
                byte secendInformaion = Serial1.readBytes();
                if ()
            } 
        }
    } 
}
Comminication::send()
{
    
}
#endif