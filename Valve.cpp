#include "Valve.h"

ValveD::ValveD(string name,volatile bool* SQL,volatile bool* SQH,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out,bool reverse):
    name{name},b_control{b_control},b_mode{b_mode},b_out{b_out},_reverse{reverse},b_t1{SQL},b_t2{SQH} {
    _exit=false;
    isClose=true;
    isClosing=false;
    isOpening=false;
    b_auto_control=old_state=old_mode=false;
    old_state=*b_mode?b_auto_control:*b_control;
    old_mode=*b_mode;
}

ValveD::~ValveD() {
    _exit=true;
}

void ValveD::loop() {
    if(!old_mode&&*b_mode) {
        printf("[%s]: Switch to auto\n",this->name.c_str());
    }
    if(old_mode&&!*b_mode) {
        printf("[%s]: Switch to manual\n",this->name.c_str());
    }
    if(*b_out!=_reverse^(*b_mode?b_auto_control:*b_control)) {
        *b_out=_reverse^(*b_mode?b_auto_control:*b_control);
    }
    if(!old_state&&*b_out) { 
        printf("[%s]: Opening\n",this->name.c_str());
        isOpening=true;
        isOpen=false;
        isClosing=false;
        isClose=false;
        t_Open=timeSinceEpochMillisec();
        endOpenTime=0;
    }
    if(old_state&&!*b_out) { 
        printf("[%s]: Closing\n",this->name.c_str());
        isOpening=false;
        isOpen=false;
        isClosing=true;
        isClose=false;
        t_Close=timeSinceEpochMillisec();
        endCloseTime=0;
    }
    old_state=*b_out;
    old_mode=*b_mode;
}
void ValveD::Open() {
    b_auto_control=true;
    *b_out=_reverse^(*b_mode?b_auto_control:*b_control);
}

void ValveD::Close() {
    b_auto_control=false;
    *b_out=_reverse^(*b_mode?b_auto_control:*b_control);
}

void ValveD::Auto() {
    *b_mode=true;
    *b_out=_reverse^(*b_mode?b_auto_control:*b_control);
}

void ValveD::Manual() {
    *b_mode=false;
    *b_out=_reverse^(*b_mode?b_auto_control:*b_control);
}

ValveA::ValveA(string name,volatile bool* SQL,volatile bool* SQH,volatile float *b_control,volatile bool *b_mode,volatile float *b_out,bool reverse):
    name{name},b_control{b_control},b_mode{b_mode},b_out{b_out},_reverse{reverse},b_t1{SQL},b_t2{SQH} {
    _exit=false;
    *b_out=_reverse?100:0;
    *b_mode=false;
    b_auto_control=0;
    *b_control=0;
}

ValveA::~ValveA() {
    _exit=true;
}

void ValveA::loop() {
    if(!old_mode && *b_mode) printf("[%s]: Auto mode\n",this->name.c_str());
    if(old_mode && !*b_mode) printf("[%s]: Manual mode\n",this->name.c_str());
    *b_out=_reverse?100-(*b_mode?b_auto_control:*b_control):(*b_mode?b_auto_control:*b_control);
    oldOut=*b_out;
    old_mode=*b_mode;
}

void ValveA::Set(int value) {
    b_auto_control=value;
    *b_out=_reverse?100-(*b_mode?b_auto_control:*b_control):(*b_mode?b_auto_control:*b_control);
}

void ValveA::Auto() {
    *b_mode=true;
    *b_out=_reverse?100-(*b_mode?b_auto_control:*b_control):(*b_mode?b_auto_control:*b_control);
}

void ValveA::Manual() {
    *b_mode=false;
    *b_out=_reverse?100-(*b_mode?b_auto_control:*b_control):(*b_mode?b_auto_control:*b_control);
}

ValveM::ValveM(string name,volatile bool* SQL,volatile bool* SQH):
    name{name},b_t1{SQL},b_t2{SQH} {
}

ValveM::~ValveM() {
}
