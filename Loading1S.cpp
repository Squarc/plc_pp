#include "Loading1S.h"


Loading1S::Loading1S(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,volatile uint16_t *set1,bool direction=false):
    name{name},f_Weight{f_Weight},b_start{b_start},f_Load{f_Load},f_Loaded{f_Loaded},set1{set1},direction{direction} {
    
    _exit=false;
    time_End=timeSinceEpochMillisec()-10000;
    _thread = thread(&Loading1S::Thread,this);
}
Loading1S::~Loading1S() {
    printf("Loading1S: Deleting\n");
    _exit=true;
    if(_thread.joinable()) _thread.join();
}

void Loading1S::Thread() {
    while(!_exit){
        bool _start=true;
        if(f_Weights[*set1-1]!=NULL) _Weight=f_Weights[*set1-1];
        else _Weight=f_Weight;
        for(auto& v:isCloseValveM) if(!v->b_t1) _start=false;
        for(auto& v:isCloseValveD) if(!v->b_t1) _start=false;
        for(auto& v:isOpenValveM) if(!v->b_t2) _start=false;
        for(auto& v:_isOpenValveM) {
            for(int i=0;i<5;i++) {
                if(v[i]!=NULL) {
                    if(*set1==i+1) {
                        if(!v[i]->b_t2) _start=false;
                    } else {
                        if(!v[i]->b_t1) _start=false;
                    }
                }
            }
        }
        _start&=*b_start;
        if(_oldHMI!=*b_start && *b_start) W_Start=*_Weight;
        if((_oldStart!=_start) && _start) {
            printf("Start %s...",name.c_str());
            for(auto& v:openValveD) {v->Auto();v->Open();}
            for(auto& v:openPump) {v->Auto();v->Start();}
            for(auto& v:closeValveD) {v->Auto();v->Close();}
            for(auto& v:_openValveD) {
                for(int i=0;i<5;i++) {
                    if((v[i])!=NULL) {
                        v[i]->Auto();
                        if(*set1==i+1) v[i]->Open(); else v[i]->Close();
                    }
                }
            }
        }
        if(_start && (direction?(*_Weight-W_Start):(W_Start-*_Weight))>=*f_Load) {
            *b_start=false; // окончание загрузки
            printf("direction:%d start:%f current:%f load:%f\n",direction,W_Start,*_Weight,*f_Load);
        }
        if((_oldStart!=_start) && !_start) {
            printf("Stop %s...",name.c_str());
            for(auto& v:openValveD) v->Close();
            for(auto& v:openPump) v->Stop();
            for(auto& v:closeValveD) v->Close();
            for(auto& v:_openValveD) {
                for(int i=0;i<5;i++)
                    if((v[i])!=NULL) v[i]->Close();
            }
            time_End=timeSinceEpochMillisec();
        }
        if(*b_start || timeSinceEpochMillisec()-time_End<10000) 
            *f_Loaded=(direction?(*_Weight-W_Start):(W_Start-*_Weight));
        _oldHMI=*b_start;
        _oldStart=_start;
        
        nsleep(300);
    }
}

void Loading1S::addOpen(ValveD* v) {
    openValveD.push_back(v);
}
void Loading1S::addOpen(Pump* v) {
    openPump.push_back(v);
}
void Loading1S::addClose(ValveD* v) {
    closeValveD.push_back(v);
}
void Loading1S::addOpen(ValveD* v1,ValveD* v2,ValveD* v3,ValveD* v4,ValveD* v5) {
    _openValveD.push_back({v1,v2,v3,v4,v5});
}
void Loading1S::addWeights(volatile float* v1,volatile float* v2,volatile float* v3,volatile float* v4,volatile float* v5) {
    f_Weights={v1,v2,v3,v4,v5};
}

void Loading1S::addIsOpen(ValveM* v) {
    isOpenValveM.push_back(v);
}
void Loading1S::addIsOpen(ValveM* v1,ValveM* v2,ValveM* v3,ValveM* v4,ValveM* v5) {
    _isOpenValveM.push_back({v1,v2,v3,v4,v5});
}

void Loading1S::addIsClose(ValveM* v) {
    isCloseValveM.push_back(v);
}
void Loading1S::addIsClose(ValveD* v) {
    isCloseValveD.push_back(v);
}

