#pragma once

#include <list>
#include <thread>
#include <stdio.h>
#include "Valve.h"
#include "Heating.h"
#include "Cooling.h"
#include "MqttDevice.h"
#include "Loading.h"
#include "Loading1S.h"

class Device
{
public:
    Device(MqttDevice *mqtt);
    ~Device();
    ValveA* addValveA(string name,volatile bool* SQL,volatile bool* SQH,volatile float *b_control,volatile bool *b_mode,volatile float *b_out,bool reverse=false);
    ValveD* addValveD(string name,volatile bool* SQL,volatile bool* SQH,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out,bool reverse=false);
    ValveM* addValveM(string name,volatile bool* SQL,volatile bool* SQH);
    Heating* addHeating(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start);
    Cooling* addCooling(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start);
    Pump* addPump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out);
    Pump* addPump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_start,volatile bool *b_stop);
    Loading* addLoading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,bool direction=false);
    Loading1S* addLoading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,volatile uint16_t *set1,bool direction=false);
    Purge* addPurge(string name,volatile bool *b_start,volatile float *f_time,volatile float *f_passed);
protected:
    bool _exit;

private:
    MqttDevice *mqtt;
    list<ValveA*> valveA;
    list<ValveD*> valveD;
    list<ValveM*> valveM;
    list<Pump*> pump;
    list<Heating*> heating;
    list<Cooling*> cooling;
    list<Loading*> loading;
    list<Loading1S*> loading1S;
    list<Purge*> purge;
    void loop();
    thread _thread;
};

