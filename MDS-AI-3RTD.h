#pragma once

#include "ModbusModule.h"

class MDS_AI_3RTD : public ModbusModule
{
public:
    MDS_AI_3RTD(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3) ;
    ~MDS_AI_3RTD() override;
    void Read() override;
    void Write() override { }

private:
    uint16_t *buffer;
    volatile float *rF1,*rF2,*rF3;
};

