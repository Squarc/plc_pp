#pragma once

#include "ModbusModule.h"

class Krohne_Optimass : public ModbusModule
{
public:
    Krohne_Optimass(modbus_t *ctx, int addr, volatile double *rFQE, volatile float *rFQ, volatile float *rT, volatile float *rD);
    ~Krohne_Optimass();
    void Read() override;
    void Write() override {};
private:
    uint16_t *buffer;
    volatile float *rFQ, *rT, *rD;
    volatile double *rFQE;
};

