#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <pigment/util.h>

class ValveD
{
public:
    ValveD(string name,volatile bool* SQL,volatile bool* SQH,volatile bool *b_control,volatile bool *b_mode,volatile bool *b_out,bool reverse=false);
    ~ValveD();
    void Open();
    void Close();
    void Auto();
    void Manual();
    bool isOpening=false, isOpen=false;
    bool isClosing=false, isClose=true;
    volatile bool *b_control,*b_mode,b_auto_control,*b_out,old_state,old_mode,*b_t1,*b_t2;
    bool error_Starting;
    bool error_t1;
    bool error_t2;
    bool _exit=false;
    long endOpenTime;
    long endCloseTime;
    uint64_t t_Open,t_Close;
    void loop();
    string name;

private:
    bool _reverse=false;
};



class ValveA
{
public:
    ValveA(string name,volatile bool* SQL,volatile bool* SQH,volatile float *b_control,volatile bool *b_mode,volatile float *b_out,bool reverse=false);
    ~ValveA();
    void Set(int value);
    void Auto();
    void Manual();

    volatile float *b_control,b_auto_control,*b_out;
    volatile bool *b_mode,*b_t1,*b_t2;
    void loop();
    string name;

private:
    bool _exit=false;
    bool _reverse=false;
    bool old_mode=false;
    float oldOut=0;

};

class ValveM
{
public:
    ValveM(string name,volatile bool* SQL,volatile bool* SQH);
    ~ValveM();
    volatile bool *b_t1,*b_t2;
    string name;

private:
};
