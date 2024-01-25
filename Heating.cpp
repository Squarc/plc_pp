#include "Heating.h"


Heating::Heating(string name,volatile float* temp,volatile float* min,volatile float* max,volatile bool* start):
    name{name},_temp{temp},_tempMin{min},_tempMax{max},_start{start} {
    _exit=false;
    _thread = thread(&Heating::Thread,this);
}

Heating::~Heating() {
    _exit=true;
    if(_thread.joinable()) _thread.join();
    openValvesA.clear();
    openValvesD.clear();
    printf("Heating: Deleting\n");
}

void Heating::Thread() {
    while(!_exit){
        bool fMan=false;
        for(auto& v:openValvesM) if(v->b_t1) fMan=true;
        for(auto& v:closeValvesM) if(v->b_t2) fMan=true;

        if((_oldStart!=(*_start && !fMan)) && (*_start && !fMan)) {
            printf("Start heating %s...",name.c_str());
            for(auto& v:openValvesA) {v->Auto();v->Set(0);}
            for(auto& v:openValvesD) {v->Auto();v->Close();}
        }
        if(*_start && !fMan) {
            cout<<*_temp<<" "<<*_tempMin<<" "<<*_tempMax<<endl;
            if(*_temp<*_tempMin) {
                for(auto& v:openValvesA) v->Set(100);
                for(auto& v:openValvesD) v->Open();
            }
            
            else if(*_temp>*_tempMax) {
                for(auto& v:openValvesA) v->Set(0);
                for(auto& v:openValvesD) v->Close();
            }
            else {
                for(auto& v:openValvesA) v->Set(100.0f*(*_temp-*_tempMax)/(*_tempMin-*_tempMax));
                for(auto& v:openValvesD) v->Close();
            }
        }
        if((_oldStart!=(*_start && !fMan)) && !(*_start && !fMan)) {
            printf("Stop heating %s...",name.c_str());
            for(auto& v:openValvesA) {v->Set(0);}
            for(auto& v:openValvesD) {v->Close();}
        }
        _oldStart = (*_start && !fMan); 

        nsleep(500);
    }
}

void Heating::addOpen(ValveA *v) {
    openValvesA.push_back(v);
}
void Heating::addOpen(ValveD *v) {
    openValvesD.push_back(v);
}
void Heating::addOpen(ValveM *v) {
    openValvesM.push_back(v);
}
void Heating::addClose(ValveM *v) {
    closeValvesM.push_back(v);
}

