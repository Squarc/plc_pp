#pragma once

#include "ModbusModule.h"

class OWEN_MV110_8AS : ModbusModule {
public:
    OWEN_MV110_8AS(modbus_t *ctx, int addr,
        volatile float *rR1,volatile float *rR2,volatile float *rR3,volatile float *rR4,volatile float *rR5,volatile float *rR6,volatile float *rR7,volatile float *rR8);
    ~OWEN_MV110_8AS() override;
    void Read() override;
    void Write() override { }
    void setFlin(int index,float x1,float y1,float x2,float y2);
private:
    float lin[8][4];
    uint16_t *buffer;
    volatile float *rR1,*rR2,*rR3,*rR4,*rR5,*rR6,*rR7,*rR8;
};

