#pragma once

#include "ModbusModule.h"

class MDS_AO_2UI : public ModbusModule
{
public:
    MDS_AO_2UI(modbus_t *ctx, int addr,
        volatile float *wF1,volatile float *wF2);
    ~MDS_AO_2UI() override;
    void Read() override { }
    void Write() override;
    void setFlin(int index,float x1,float y1,float x2,float y2);

private:
    uint16_t *buffer;
    volatile float *wF1,*wF2;
    float lin[2][4];

};

