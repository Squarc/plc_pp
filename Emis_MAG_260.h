#pragma once

#include "ModbusModule.h"

class Emis_MAG_260 : public ModbusModule
{
public:
    Emis_MAG_260(modbus_t *ctx, int addr, volatile float *rF);
    ~Emis_MAG_260() override;
    void Read() override;
    void Write() override {};

private:
    uint16_t *buffer;
    volatile float *rF;
};

