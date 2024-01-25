#pragma once

#include <iostream>
#include "Valve.h"
#include <list>
#include <string.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


class Heating
{
public:
    Heating(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start);
    ~Heating();
    void addOpen(ValveA *v);
    void addOpen(ValveD *v);
    void addOpen(ValveM *v);
    void addClose(ValveM *v);
    bool _oldStart=false;
    volatile bool* _start;
    volatile float *_temp;
    string name;
    volatile float* _tempMin;
    volatile float* _tempMax;
    void Thread();

private:
    bool _exit;
    thread _thread;
    list<ValveD*> openValvesD;
    list<ValveA*> openValvesA;
    list<ValveM*> openValvesM;
    list<ValveM*> closeValvesM;
};

