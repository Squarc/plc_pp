#pragma once

#include "ModbusModule.h"

class MDS_DIO_44 : ModbusModule {
public:
    MDS_DIO_44(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4);
    ~MDS_DIO_44() override;
    void Read() override;
    void Write() override;

private:
    uint16_t *buffer;
    volatile bool *rB1,*rB2,*rB3,*rB4,*wB1,*wB2,*wB3,*wB4;
};

