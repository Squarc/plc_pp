#pragma once

#include "ModbusModule.h"

class OWEN_TRM202 : ModbusModule {
public:
    OWEN_TRM202(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2);
    ~OWEN_TRM202() override;
    void Read() override;
    void Write() override { }
private:
    uint16_t *buffer;
    volatile float *rF1,*rF2;
};
