#pragma once

#include "ModbusModule.h"

class MicroMotion : public ModbusModule
{
public:
    MicroMotion(modbus_t *ctx, int addr, volatile float *massTotal, bool setNullable=false);
    ~MicroMotion() override;
    void Read() override;
    void Write() override;
private:
    uint16_t *buffer;
    volatile float *massTotal;
};

