#pragma once

#include "ModbusModule.h"

class OWEN_PLC110_60 : ModbusModule {
public:
    OWEN_PLC110_60(modbus_t *ctx, int addr,
        volatile bool *rB1, volatile bool *rB2, volatile bool *rB3, volatile bool *rB4,
        volatile bool *rB5, volatile bool *rB6, volatile bool *rB7, volatile bool *rB8,
        volatile bool *rB9, volatile bool *rB10, volatile bool *rB11, volatile bool *rB12,
        volatile bool *rB13, volatile bool *rB14, volatile bool *rB15, volatile bool *rB16,
        volatile bool *rB17, volatile bool *rB18, volatile bool *rB19, volatile bool *rB20,
        volatile bool *rB21, volatile bool *rB22, volatile bool *rB23, volatile bool *rB24,
        volatile bool *rB25, volatile bool *rB26, volatile bool *rB27, volatile bool *rB28,
        volatile bool *rB29, volatile bool *rB30, volatile bool *rB31, volatile bool *rB32,
        volatile bool *rB33, volatile bool *rB34, volatile bool *rB35, volatile bool *rB36,
        volatile bool *wB1, volatile bool *wB2, volatile bool *wB3, volatile bool *wB4,
        volatile bool *wB5, volatile bool *wB6, volatile bool *wB7, volatile bool *wB8,
        volatile bool *wB9, volatile bool *wB10, volatile bool *wB11, volatile bool *wB12,
        volatile bool *wB13, volatile bool *wB14, volatile bool *wB15, volatile bool *wB16,
        volatile bool *wB17, volatile bool *wB18, volatile bool *wB19, volatile bool *wB20,
        volatile bool *wB21, volatile bool *wB22, volatile bool *wB23, volatile bool *wB24);
    ~OWEN_PLC110_60() override;
    void Read() override;
    void Write() override;
    void setReverse(int index);

private:
    uint16_t *buffer;
    volatile bool *rB1,*rB2,*rB3,*rB4,*rB5,*rB6,*rB7,*rB8,*rB9,*rB10,*rB11,*rB12,
        *rB13,*rB14,*rB15,*rB16,*rB17,*rB18,*rB19,*rB20,*rB21,*rB22,*rB23,*rB24,
        *rB25,*rB26,*rB27,*rB28,*rB29,*rB30,*rB31,*rB32,*rB33,*rB34,*rB35,*rB36,
        *wB1,*wB2,*wB3,*wB4,*wB5,*wB6,*wB7,*wB8,*wB9,*wB10,*wB11,*wB12,
        *wB13,*wB14,*wB15,*wB16,*wB17,*wB18,*wB19,*wB20,*wB21,*wB22,*wB23,*wB24;
    bool r1=false,r2=false,r3=false,r4=false,r5=false,r6=false,r7=false,r8=false,r9=false,r10=false,r11=false,r12=false,r13=false,r14=false,r15=false,r16=false,
        r17=false,r18=false,r19=false,r20=false,r21=false,r22=false,r23=false,r24=false;

};

