#pragma once

#include "ModbusModule.h"

class MDS_AIO_4 : public ModbusModule
{
public:
    MDS_AIO_4(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile float *wF1,volatile float *wF2,volatile float *wF3,volatile float *wF4);
    ~MDS_AIO_4() override;
    void Read() override;
    void Write() override;
    void setReverce(int index);
private:
    uint16_t *buffer;
    volatile float *rF1,*rF2,*rF3,*rF4;
    volatile float *wF1,*wF2,*wF3,*wF4;
    volatile bool *rB1,*rB2,*rB3,*rB4;
    bool rev[4];
};

