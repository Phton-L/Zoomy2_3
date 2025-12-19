/*
created by: Vinzent Schillinger
date: 17.12.2025
*/

#ifndef COMMINICATION_H
#define COMMINICATION_H

#include <Arduino.h>

class Comminication
{
    private:
        byte _start;
        byte _end;
        int _bout;
        boolean _serial1Bol;
    public:
        Comminication();
        void begin(byte start,byte end,int bout,boolean serial1Bol);

        void read(int &direktionSend,int &speedSend);

        void send(int direktionSend,int speedSend);


};

#endif