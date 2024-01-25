#include "Pump.h"


Pump::Pump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out):
    name{name},b_control{b_control},b_mode{b_mode},b_out{b_out},b_start{NULL},b_stop{NULL} {
    _exit=false;
    b_auto_control=old_state=old_mode=false;
    old_state=*b_mode?b_auto_control:*b_control;
    old_mode=*b_mode;
    _thread = thread(&Pump::Thread,this);
}
Pump::Pump(string name,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_start,volatile bool *b_stop):
    name{name},b_control{b_control},b_mode{b_mode},b_out{&out},b_start{b_start},b_stop{b_stop} {
    _exit=false;
    b_auto_control=old_state=old_mode=false;
    old_state=*b_mode?b_auto_control:*b_control;
    old_mode=*b_mode;
    _thread = thread(&Pump::Thread,this);
}

Pump::~Pump() {
    printf("[%s] Pump: Deleting\n", this->name.c_str());
    _exit=true;
    if(_thread.joinable()) _thread.join();
}

void Pump::Thread() {
    while(!_exit) {
        auto currentTime = timeSinceEpochMillisec();
        if(!old_mode&&*b_mode) {
            printf("[%s]: Switch to auto\n",this->name.c_str());
        }
        if(old_mode&&!*b_mode) {
            printf("[%s]: Switch to manual\n",this->name.c_str());
        }
        if(*b_out!=(*b_mode?b_auto_control:*b_control))
            *b_out=(*b_mode?b_auto_control:*b_control);
        if(!old_state&&*b_out) { 
            printf("[%s]: Starting\n",this->name.c_str());
            if(b_start!=NULL) *b_start=true;
            if(b_stop!=NULL) *b_stop=false;
            t_Start=currentTime;
            t_Stop=0;
        }
        if(old_state&&!*b_out) { 
            printf("[%s]: Stopping\n",this->name.c_str());
            if(b_start!=NULL) *b_start=false;
            if(b_stop!=NULL) *b_stop=true;
            t_Stop=currentTime;
            t_Start=0;
        }
        if(b_start!=NULL)
            if((currentTime-t_Start>3000) && *b_start) *b_start=false;
        if(b_stop!=NULL)
            if((currentTime-t_Stop>3000) && *b_stop) *b_stop=false;
        old_state=*b_out;
        old_mode=*b_mode;
        nsleep(300);
    }
}
void Pump::Start() {
    bool oldOut=*b_out;
    b_auto_control=true;
    *b_out=*b_mode?b_auto_control:*b_control;
}

void Pump::Stop() {
    bool oldOut=*b_out;
    b_auto_control=false;
    *b_out=*b_mode?b_auto_control:*b_control;
}

void Pump::Auto() {
    *b_mode=true;
    *b_out=*b_mode?b_auto_control:*b_control;
}

void Pump::Manual() {
    *b_mode=false;
    *b_out=*b_mode?b_auto_control:*b_control;
}
