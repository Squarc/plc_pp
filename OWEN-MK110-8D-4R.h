#pragma once

#include "ModbusModule.h"

class OWEN_MK110_8D_4R : ModbusModule {
public:
    OWEN_MK110_8D_4R(modbus_t *ctx, int addr,
    volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
    volatile float *wR1,volatile float *wR2,volatile float *wR3,volatile float *wR4,
    bool setNullable=false);
    ~OWEN_MK110_8D_4R() override;
    void Read() override;
    void Write() override;

private:
    volatile float *wR1,*wR2,*wR3,*wR4;
    volatile bool *rB1,*rB2,*rB3,*rB4;
    uint16_t *buffer;
};

