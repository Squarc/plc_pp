#pragma once

#include "ModbusModule.h"

class Elemer_UR31 : public ModbusModule
{
public:
    Elemer_UR31(modbus_t *ctx, int addr, volatile float *rF);
    ~Elemer_UR31() override;
    void Read() override;
    void Write() override {};

private:
    uint16_t *buffer;
    volatile float *rF;
};

