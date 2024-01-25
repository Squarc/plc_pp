#pragma once

#include "ModbusModule.h"

class MDS_DIO_16BD : public ModbusModule
{
public:
    MDS_DIO_16BD(modbus_t *ctx, int addr,
        volatile bool *rB1=NULL,volatile bool *rB2=NULL,volatile bool *rB3=NULL,volatile bool *rB4=NULL,
        volatile bool *rB5=NULL,volatile bool *rB6=NULL,volatile bool *rB7=NULL,volatile bool *rB8=NULL,
        volatile bool *rB9=NULL,volatile bool *rB10=NULL,volatile bool *rB11=NULL,volatile bool *rB12=NULL,
        volatile bool *rB13=NULL,volatile bool *rB14=NULL,volatile bool *rB15=NULL,volatile bool *rB16=NULL,
        volatile bool *wB1=NULL,volatile bool *wB2=NULL,volatile bool *wB3=NULL,volatile bool *wB4=NULL,
        volatile bool *wB5=NULL,volatile bool *wB6=NULL,volatile bool *wB7=NULL,volatile bool *wB8=NULL,
        volatile bool *wB9=NULL,volatile bool *wB10=NULL,volatile bool *wB11=NULL,volatile bool *wB12=NULL,
        volatile bool *wB13=NULL,volatile bool *wB14=NULL,volatile bool *wB15=NULL,volatile bool *wB16=NULL,
        volatile uint16_t *rC1=NULL,volatile uint16_t *rC2=NULL,volatile uint16_t *rC3=NULL,volatile uint16_t *rC4=NULL,
        volatile bool *wReset1=NULL,volatile bool *wReset2=NULL,volatile bool *wReset3=NULL,volatile bool *wReset4=NULL);
    ~MDS_DIO_16BD() override;
    void Write() override;
    void Read() override;
    void setRev(int index);

private:
    uint16_t *buffer;
    volatile bool *rB1,*rB2,*rB3,*rB4,*rB5,*rB6,*rB7,*rB8,*rB9,*rB10,*rB11,*rB12,*rB13,*rB14,*rB15,*rB16,
        *wB1,*wB2,*wB3,*wB4,*wB5,*wB6,*wB7,*wB8,*wB9,*wB10,*wB11,*wB12,*wB13,*wB14,*wB15,*wB16;
    volatile uint16_t *rC1,*rC2,*rC3,*rC4;
    volatile bool *wReset1,*wReset2,*wReset3,*wReset4;
    bool rev[16];

};

