#pragma once

#include "ModbusModule.h"

class TenzoM_TV006c : public ModbusModule
{
public:
    TenzoM_TV006c(modbus_t *ctx, int addr, volatile float *rF1=NULL, int rev=0, bool setNullable=false);
    ~TenzoM_TV006c();
    void Read();
    void Write() { }
private:
    uint16_t *buffer;
    int rev;
    volatile float *rF1;
};
