#pragma once

#include "ModbusModule.h"

class OWEN_PLC160 : ModbusModule {
public:
    OWEN_PLC160(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
        volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
        volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8,
        volatile float *rF9,
        volatile float *rC1,volatile float *rC2,volatile float *rC3,volatile float *rC4,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
        volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
        volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
        volatile float *wF1,volatile float *wF2,volatile float *wF3,volatile float *wF4,
        volatile bool *wReset);
    ~OWEN_PLC160() override;
    void Read() override;
    void Write() override;
    void setFlin(int index,float x1,float y1,float x2,float y2);

private:
    volatile bool *rB1,*rB2,*rB3,*rB4,*rB5,*rB6,*rB7,*rB8,
        *rB9,*rB10,*rB11,*rB12,*rB13,*rB14,*rB15,*rB16;

    volatile float *rF1,*rF2,*rF3,*rF4,*rF5,*rF6,*rF7,*rF8,*rF9;
    volatile float *rC1,*rC2,*rC3,*rC4;
    volatile bool *wB1,*wB2,*wB3,*wB4,*wB5,*wB6,*wB7,*wB8,*wB9,*wB10,*wB11,*wB12,*wReset;
    volatile float *wF1,*wF2,*wF3,*wF4;
    uint16_t *buffer;
    float lin[13][4];
};

