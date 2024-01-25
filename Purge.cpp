#include "Purge.h"


Purge::Purge(string name,volatile bool *b_start,volatile float *f_time,volatile float *f_passed):
    name{name},b_start{b_start},f_time{f_time},f_passed{f_passed} {
    _exit=false;
    _thread = thread(&Purge::Thread,this);
}
Purge::~Purge() {
    printf("Purge: Deleting");
    openValvesD.clear();
    closeValvesD.clear();
    openValvesA.clear();
    closeValvesA.clear();
    isOpenValvesM.clear();
    isCloseValvesM.clear();
    _exit=true;
    if(_thread.joinable()) _thread.join();
}
void Purge::Thread() {
    while(!_exit){
        auto currentTime=timeSinceEpochMillisec();
        bool _start=true;
        _pause=*b_start && !_start;
        for(auto& v:isCloseValvesM) if(!v->b_t1) _start=false;
        for(auto& v:isCloseValvesD) if(!v->b_t1) _start=false;
        for(auto& v:isOpenValvesM) if(!v->b_t2) _start=false;
        _start&=*b_start;

        if((_oldStart!=_start) && _start) {
            printf("Start purge...\n");
            time_Start=currentTime;
            for(ValveD *v:openValvesD) {
                v->Auto();
                v->Open();
            }
            for(ValveD *v:closeValvesD) {
                v->Auto();
                v->Close();
            }
            for(ValveA *v:openValvesA) {
                v->Auto();
                v->Set(100);
            }
            for(ValveA *v:closeValvesA) {
                v->Auto();
                v->Set(0);
            }
        }
        if((_oldStart!=_start) && !_start) {
            printf("Stop purge...\n");
            for(ValveD *v:openValvesD) {
                v->Auto();
                v->Close();
            }
            for(ValveD *v:closeValvesD) {
                v->Auto();
                v->Close();
            }
            for(ValveA *v:openValvesA) {
                v->Auto();
                v->Set(0);
            }
            for(ValveA *v:closeValvesA) {
                v->Auto();
                v->Set(0);
            }
        }
        if(_oldPause!=_pause && _pause) pauseTime=currentTime;
        if(_oldPause!=_pause && !_pause) time_Start+=(currentTime-pauseTime);
        uint64_t shiftTime=_pause?(currentTime-pauseTime):0;
        
        if(_start && currentTime-time_Start-shiftTime>(*f_time*60000.0f)) *b_start=false;
        if(*b_start) *f_passed=(currentTime-time_Start-shiftTime)/60000.0f;
        _oldPause=_pause;
        _oldStart=_start;
        _oldHMI=*b_start;
        nsleep(1000);
    }
    /* Free the memory */

    /* Close the connection */
}

void Purge::AddOpenValve(ValveD *valve){
    openValvesD.push_back(valve);
}
void Purge::AddCloseValve(ValveD *valve){
    closeValvesD.push_back(valve);
}
void Purge::AddOpenValve(ValveA *valve){
    openValvesA.push_back(valve);
}
void Purge::AddCloseValve(ValveA *valve){
    closeValvesA.push_back(valve);
}
void Purge::AddIsOpenValve(ValveM *valve){
    isOpenValvesM.push_back(valve);
}
void Purge::AddIsCloseValve(ValveM *valve){
    isCloseValvesM.push_back(valve);
}
void Purge::AddIsCloseValve(ValveD *valve){
    isCloseValvesD.push_back(valve);
}
