#pragma once

#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <pigment/util.h>

class Pump
{
public:
    Pump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out);
    Pump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_start,volatile bool *b_stop);
    ~Pump();
    void Start();
    void Stop();
    void Auto();
    void Manual();
    volatile bool *b_control,*b_mode,*b_out,*b_start,*b_stop;
    string name;
private:
    bool b_auto_control,old_state,old_mode,state;
    bool _exit,out=false;
    uint64_t t_Start=0,t_Stop=0;
    void Thread();
    thread _thread;

};
