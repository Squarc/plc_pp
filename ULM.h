#pragma once

#include "ModbusModule.h"

class ULM : public ModbusModule
{
public:
    ULM(modbus_t *ctx, int addr, volatile float *level=NULL);
    ~ULM();
    void Read() override;
    void Write() override {}
private:
    uint16_t *buffer;
    float oldValue;
    volatile float *level;
};

