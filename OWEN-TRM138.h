#pragma once

#include "ModbusModule.h"

class OWEN_TRM138 : ModbusModule {
public:
    OWEN_TRM138(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8);
    ~OWEN_TRM138() override;
    void Read() override;
    void Write() override { }
private:
    uint16_t *buffer;
    volatile float *rF1,*rF2,*rF3,*rF4,*rF5,*rF6,*rF7,*rF8;
};

