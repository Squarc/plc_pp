#pragma once

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pigment/util.h>
#include <pigment/Logger.h> 
#include <string.h>
#include "ModbusModule.h"

class Delta_C2000 : public ModbusModule
{
public:
    Delta_C2000(modbus_t *ctx, int addr,volatile float *frq=NULL,volatile float *current=NULL,volatile bool *autostart=NULL,volatile bool *bStart=NULL,volatile bool *bStop=NULL,volatile bool *_state=NULL);
    ~Delta_C2000();
    void Read() override;
    void Write() override;
    void Start();
    void Stop();
private:
    Logger *log;
    int wE1=0,wE2=0,rE1=0;
    uint16_t *buffer;
    volatile float *frq,*current;
    bool _start=false;
    volatile bool *bStart,*bStop,*_autostart,*_state;
    int state=0;
    uint64_t tStart=0,tStop=0;
};


