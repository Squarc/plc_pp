#include "Device.h"

Device::Device(MqttDevice *mqtt):mqtt{mqtt} {
    _exit=false;

    _thread = thread(&Device::loop,this);
}
Device::~Device() {
    _exit=true;
    if(_thread.joinable()) _thread.join();
    for(auto& v:valveA) delete v;
    for(auto& v:valveD) delete v;
    for(auto& v:valveM) delete v;
    for(auto& v:pump) delete v;
    for(auto& v:heating) delete v;
    for(auto& v:loading) delete v;
    for(auto& v:loading1S) delete v;
    for(auto& v:purge) delete v;

    printf("Device delete\n");
}

void Device::loop() {
    while(!_exit) {
        for(auto& v:valveA) v->loop();
        for(auto& v:valveD) v->loop();
        nsleep(300);
    }
}
ValveA* Device::addValveA(string name,volatile bool* SQL,volatile bool* SQH,volatile float *b_control,volatile bool *b_mode,volatile float *b_out,bool reverse) {
    ValveA* v=new ValveA(name,SQL,SQH,b_control,b_mode,b_out,reverse);
    if(mqtt!=NULL) mqtt->add(v);
    valveA.push_back(v);
    return v;
}
ValveD* Device::addValveD(string name,volatile bool* SQL,volatile bool* SQH,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out,bool reverse) {
    ValveD* v=new ValveD(name,SQL,SQH,b_control,b_mode,b_out,reverse);
    if(mqtt!=NULL) mqtt->add(v);
    valveD.push_back(v);
    return v;
}
ValveM* Device::addValveM(string name,volatile bool* SQL,volatile bool* SQH) {
    ValveM* v=new ValveM(name,SQL,SQH);
    if(mqtt!=NULL) mqtt->add(v);
    valveM.push_back(v);
    return v;
}
Heating* Device::addHeating(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start) {
    Heating* v=new Heating(name,temp,min,max,start);
    if(mqtt!=NULL) mqtt->add(v);
    heating.push_back(v);
    return v;
}
Cooling* Device::addCooling(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start) {
    Cooling* v=new Cooling(name,temp,min,max,start);
    if(mqtt!=NULL) mqtt->add(v);
    cooling.push_back(v);
    return v;
}
Pump* Device::addPump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out) {
    Pump* v=new Pump(name,b_control,b_mode,b_out);
    if(mqtt!=NULL) mqtt->add(v);
    pump.push_back(v);
    return v;
}
Pump* Device::addPump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_start,volatile bool *b_stop) {
    Pump* v=new Pump(name,b_control,b_mode,b_start,b_stop);
    if(mqtt!=NULL) mqtt->add(v);
    pump.push_back(v);
    return v;
}
Loading* Device::addLoading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,bool direction) {
    Loading* v=new Loading(name,f_Weight,b_start,f_Load,f_Loaded,direction);
    if(mqtt!=NULL) mqtt->add(v);
    loading.push_back(v);
    return v;
}
Loading1S* Device::addLoading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,volatile uint16_t *set1,bool direction) {
    Loading1S* v=new Loading1S(name,f_Weight,b_start,f_Load,f_Loaded,set1,direction);
    if(mqtt!=NULL) mqtt->add(v);
    loading1S.push_back(v);
    return v;
}
Purge* Device::addPurge(string name,volatile bool *b_start,volatile float *f_time,volatile float *f_passed) {
    Purge* v=new Purge(name,b_start,f_time,f_passed);
    if(mqtt!=NULL) mqtt->add(v);
    purge.push_back(v);
    return v;
}
