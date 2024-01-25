#pragma once

#include "Valve.h"
#include <list>
#include <thread>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pigment/util.h>

class Purge
{
public:
    Purge(string name,volatile bool *b_start,volatile float *f_time,volatile float *f_passed);
    ~Purge();
    std::list<ValveD*> openValvesD;
    std::list<ValveD*> closeValvesD;
    std::list<ValveA*> openValvesA;
    std::list<ValveA*> closeValvesA;
    std::list<ValveM*> isOpenValvesM;
    std::list<ValveM*> isCloseValvesM;
    std::list<ValveD*> isCloseValvesD;

    void AddOpenValve(ValveD *valve);
    void AddCloseValve(ValveD *valve);
    void AddOpenValve(ValveA *valve);
    void AddCloseValve(ValveA *valve);
    void AddIsOpenValve(ValveM *valve);
    void AddIsCloseValve(ValveM *valve);
    void AddIsCloseValve(ValveD *valve);

    volatile bool *b_start;
    bool _oldStart=false,_oldHMI=false,_oldPause=false,_pause=false;
    uint64_t time_Start=0; // время старта
    uint64_t pauseTime=0;
    volatile float *f_time,*f_passed;
    string name;

private:
    void Thread();
    thread _thread;
    bool _exit;
};
