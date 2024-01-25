#pragma once

#include <string.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "Valve.h"
#include <list>

class Loading
{
public:
    Loading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,bool direction);
    ~Loading();
    void addOpen(ValveD* v);
    void addClose(ValveD* v);
    void addIsOpen(ValveM* v);
    void addIsClose(ValveM* v);
    void addIsClose(ValveD* v);
    volatile float *f_Weight,*f_Load,*f_Loaded;
    volatile bool *b_start;
    uint64_t time_End=0; // время старта
    float W_Start;
    float T_Start;

    bool _oldStart=false,_oldHMI=false;
    float _load=0, _loaded=0;
    float _oldLoaded;
    std::string name;
protected:
    list<ValveD*> openValveD;
    list<ValveD*> closeValveD;
    list<ValveM*> isCloseValveM;
    list<ValveM*> isOpenValveM;
    list<ValveD*> isCloseValveD;
    bool direction=false;

    bool _exit;
    void Thread();
    thread _thread;

};

