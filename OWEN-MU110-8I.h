#pragma once

#include "ModbusModule.h"

class OWEN_MU110_8I : ModbusModule {
public:
    OWEN_MU110_8I(modbus_t *ctx, int addr,
        volatile float *wR1,volatile float *wR2,volatile float *wR3,volatile float *wR4,
        volatile float *wR5,volatile float *wR6,volatile float *wR7,volatile float *wR8);
    ~OWEN_MU110_8I() override;
    void Read() override {}
    void Write() override;
    void setFlin(int index,float x1,float y1,float x2,float y2);

private:
    uint16_t *buffer;
    volatile float *wR1, *wR2, *wR3, *wR4, *wR5, *wR6, *wR7, *wR8;
    float lin[8][4];
};

