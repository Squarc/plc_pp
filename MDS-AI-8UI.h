#pragma once

#include "ModbusModule.h"

class MDS_AI_8UI : public ModbusModule
{
public:
    MDS_AI_8UI(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8);
    ~MDS_AI_8UI() override;
    void Read() override;
    void Write() override { }
    void setFlin(int index,float x1,float y1,float x2,float y2);

private:
    float lin[8][4];
    uint16_t *buffer;
    volatile float *rF1,*rF2,*rF3,*rF4,*rF5,*rF6,*rF7,*rF8;
};

