#pragma once

#include "ModbusModule.h"

class OWEN_MV110_16DN : ModbusModule {
public:
    OWEN_MV110_16DN(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
        volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
        volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16);
    ~OWEN_MV110_16DN() override;
    void Read() override;
    void Write() override { }
private:
    uint16_t *buffer;
    volatile bool *rB1,*rB2,*rB3,*rB4,*rB5,*rB6,*rB7,*rB8,
        *rB9,*rB10,*rB11,*rB12,*rB13,*rB14,*rB15,*rB16;
};

