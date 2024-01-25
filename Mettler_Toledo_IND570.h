#pragma once

#include "ModbusModule.h"

class Mettler_Toledo_IND570 : public ModbusModule
{
public:
    Mettler_Toledo_IND570(modbus_t *ctx, int addr, volatile float *weight=NULL);
    ~Mettler_Toledo_IND570();
    void Read() override;
    void Write() override {}
private:
    uint16_t *buffer;
    float oldValue;
    volatile float *weight;
};

