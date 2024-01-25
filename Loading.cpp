#include "Loading.h"

Loading::Loading(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,bool direction=false):
    name{name},f_Weight{f_Weight},b_start{b_start},f_Load{f_Load},f_Loaded{f_Loaded},direction{direction} {
    
    _exit=false;
    time_End=timeSinceEpochMillisec()-10000;
    _thread = thread(&Loading::Thread,this);
}
Loading::~Loading() {
    printf("Loading: Deleting\n");
    _exit=true;
    if(_thread.joinable()) _thread.join();
}

void Loading::Thread() {
    while(!_exit){
        bool _start=true;
        for(auto& v:isCloseValveM) if(!v->b_t1) _start=false;
        for(auto& v:isCloseValveD) if(!v->b_t1) _start=false;
        for(auto& v:isOpenValveM) if(!v->b_t2) _start=false;
        _start&=*b_start;
        if(_oldHMI!=*b_start) W_Start=*f_Weight;
        if((_oldStart!=_start) && _start) {
            printf("Start %s...",name.c_str());
            for(auto& v:openValveD) {v->Auto();v->Open();}
            for(auto& v:closeValveD) {v->Auto();v->Close();}
        }
        if(_start && (direction?(*f_Weight-W_Start):(W_Start-*f_Weight))>=*f_Load) *b_start=false; // окончание загрузки
        if((_oldStart!=_start) && !_start) {
            printf("Stop %s...",name.c_str());
            for(auto& v:openValveD) v->Close();
            for(auto& v:closeValveD) v->Close();
            time_End=timeSinceEpochMillisec();
        }
        if(_start || timeSinceEpochMillisec()-time_End<10000) 
        _oldHMI=*b_start;
        _oldStart=_start;
        
        nsleep(300);
    }
}

void Loading::addOpen(ValveD* v) {
    openValveD.push_back(v);
}
void Loading::addClose(ValveD* v) {
    closeValveD.push_back(v);
}
void Loading::addIsOpen(ValveM* v) {
    isOpenValveM.push_back(v);
}
void Loading::addIsClose(ValveM* v) {
    isCloseValveM.push_back(v);
}
void Loading::addIsClose(ValveD* v) {
    isCloseValveD.push_back(v);
}

