/*
created by: Vinzent Schillinger
date: 17.12.2025
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>

class Communication
{
    private:
        byte _start;
        byte _end;
        int _bout;
        boolean _serial1Bol;
    public:

    public:
        Communication();

        void begin(byte start,byte end,int bout,bool serial1Bol);

        void read(int &directionSend,int &speedSend);

        void send(int directionSend,int speedSend);


};

#endif