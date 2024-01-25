#pragma once

#include <string.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "Valve.h"
#include "Pump.h"
#include <list>
template <class T>
struct Valves {
    Valves():v1{NULL},v2{NULL},v3{NULL},v4{NULL},v5{NULL} {}
    Valves(T*v1,T*v2,T*v3,T*v4,T*v5):v1{v1},v2{v2},v3{v3},v4{v4},v5{v5} {}
    T *v1,*v2,*v3,*v4,*v5;
    T* operator[](int i) {
        if(i==0) return v1;
        else if(i==1) return v2;
        else if(i==2) return v3;
        else if(i==3) return v4;
        else if(i==4) return v5;
        else return NULL;
    }
};

class Loading1S
{
public:
    Loading1S(string name,volatile float *f_Weight,volatile bool *b_start,volatile float *f_Load, volatile float *f_Loaded,volatile uint16_t *set1,bool direction);
    ~Loading1S();
    void addOpen(ValveD* v);
    void addOpen(Pump* v);
    void addClose(ValveD* v);
    void addOpen(ValveD* v1,ValveD* v2,ValveD* v3,ValveD* v4,ValveD* v5);
    void addWeights(volatile float* v1,volatile float* v2,volatile float* v3,volatile float* v4,volatile float* v5);
    void addIsOpen(ValveM* v);
    void addIsOpen(ValveM* v1,ValveM* v2,ValveM* v3,ValveM* v4,ValveM* v5);
    void addIsClose(ValveM* v);
    void addIsClose(ValveD* v);
    volatile float *f_Weight,*f_Load,*f_Loaded;
    volatile float *_Weight;
    Valves<volatile float> f_Weights;
    volatile bool *b_start;
    volatile uint16_t *set1;
    uint64_t time_End=0; // время старта
    float W_Start;
    float T_Start;

    bool _oldStart=false,_oldHMI=false;
    float _load=0, _loaded=0;
    float _oldLoaded;
    std::string name;
    bool direction=false;
protected:
    list<ValveD*> openValveD;
    list<Pump*> openPump;
    list<ValveD*> closeValveD;
    list<ValveM*> isCloseValveM;
    list<ValveM*> isOpenValveM;
    list<Valves<ValveM> > _isOpenValveM; //1S
    list<ValveD*> isCloseValveD;
    list<Valves<ValveD> > _openValveD; //1S



    bool _exit;
    void Thread();
    thread _thread;

};

