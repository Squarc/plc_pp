#pragma once

#include "ModbusModule.h"

class OWEN_MU110_16R : ModbusModule {
public:
    OWEN_MU110_16R(modbus_t *ctx, int addr,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
        volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
        volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
        volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16);
    ~OWEN_MU110_16R() override;
    void Read() override {}
    void Write() override;
    void setReverse(int index);

private:
    uint16_t *buffer;
    volatile bool *wB1,*wB2,*wB3,*wB4,*wB5,*wB6,*wB7,*wB8,
        *wB9,*wB10,*wB11,*wB12,*wB13,*wB14,*wB15,*wB16;
    bool r1=false,r2=false,r3=false,r4=false,r5=false,r6=false,r7=false,r8=false,r9=false,r10=false,r11=false,r12=false,r13=false,r14=false,r15=false,r16=false;
};

