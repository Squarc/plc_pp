#pragma once

#include <thread>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <modbus.h>
#include <memory>
#include <pigment/Delta_C2000.h>
#include <pigment/ModbusModule.h>
#include <pigment/MDS-AI-8UI.h>
#include <pigment/MDS-DIO-16BD.h>
#include <pigment/MDS-AO-2UI.h>
#include <pigment/MDS-AI-3RTD.h>
#include <pigment/MDS-DIO-44.h>
#include <pigment/MDS-AIO-4.h>
#include <pigment/OWEN-TRM138.h>
#include <pigment/OWEN-TRM202.h>
#include <pigment/OWEN-MV110-16DN.h>
#include <pigment/OWEN-MU110-16R.h>
#include <pigment/OWEN-MV110-8AS.h>
#include <pigment/OWEN-MV110-8A.h>
#include <pigment/OWEN-MU110-8I.h>
#include <pigment/OWEN-PLC110.60.h>
#include <pigment/OWEN-PLC160.h>
#include <pigment/TenzoM_TV006c.h>
#include <pigment/MicroMotion.h>
#include <pigment/Emis_MAG_260.h>
#include <pigment/Elemer_UR31.h>
#include <pigment/Krohne_Optimass.h>
#include <pigment/Mettler_Toledo_IND570.h>
#include <pigment/ULM.h>

class ModbusLine
{
public:

    ModbusLine(modbus_t *ctx, long sleepTime=300);
    ~ModbusLine();
    void addOWEN_TRM138(int address,volatile float *rF1=NULL,volatile float *rF2=NULL,volatile float *rF3=NULL,volatile float *rF4=NULL,
        volatile float *rF5=NULL,volatile float *rF6=NULL,volatile float *rF7=NULL,volatile float *rF8=NULL);
    void addOWEN_TRM202(int address,volatile float *rF1=NULL,volatile float *rF2=NULL);
    void addOWEN_MV110_16DN(int address,volatile bool *rB1=NULL,volatile bool *rB2=NULL,volatile bool *rB3=NULL,volatile bool *rB4=NULL,
        volatile bool *rB5=NULL,volatile bool *rB6=NULL,volatile bool *rB7=NULL,volatile bool *rB8=NULL,
        volatile bool *rB9=NULL,volatile bool *rB10=NULL,volatile bool *rB11=NULL,volatile bool *rB12=NULL,
        volatile bool *rB13=NULL,volatile bool *rB14=NULL,volatile bool *rB15=NULL,volatile bool *rB16=NULL);
    OWEN_MU110_16R* addOWEN_MU110_16R(int addr,
        volatile bool *wB1=NULL,volatile bool *wB2=NULL,volatile bool *wB3=NULL,volatile bool *wB4=NULL,
        volatile bool *wB5=NULL,volatile bool *wB6=NULL,volatile bool *wB7=NULL,volatile bool *wB8=NULL,
        volatile bool *wB9=NULL,volatile bool *wB10=NULL,volatile bool *wB11=NULL,volatile bool *wB12=NULL,
        volatile bool *wB13=NULL,volatile bool *wB14=NULL,volatile bool *wB15=NULL,volatile bool *wB16=NULL);
    MDS_AI_8UI* addMDS_AI_8UI(int address,
        volatile float *rF1=NULL,volatile float *rF2=NULL,volatile float *rF3=NULL,volatile float *rF4=NULL,
        volatile float *rF5=NULL,volatile float *rF6=NULL,volatile float *rF7=NULL,volatile float *rF8=NULL);
    MDS_DIO_16BD* addMDS_DIO_16BD(int address,
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
    MDS_DIO_16BD* addMDS_DIO_16BD_W(int address,
        volatile bool *wB1=NULL,volatile bool *wB2=NULL,volatile bool *wB3=NULL,volatile bool *wB4=NULL,
        volatile bool *wB5=NULL,volatile bool *wB6=NULL,volatile bool *wB7=NULL,volatile bool *wB8=NULL,
        volatile bool *wB9=NULL,volatile bool *wB10=NULL,volatile bool *wB11=NULL,volatile bool *wB12=NULL,
        volatile bool *wB13=NULL,volatile bool *wB14=NULL,volatile bool *wB15=NULL,volatile bool *wB16=NULL,
        volatile uint16_t *rC1=NULL,volatile uint16_t *rC2=NULL,volatile uint16_t *rC3=NULL,volatile uint16_t *rC4=NULL,
        volatile bool *wReset1=NULL,volatile bool *wReset2=NULL,volatile bool *wReset3=NULL,volatile bool *wReset4=NULL);
    MDS_AO_2UI* addMDS_AO_2UI(int addr,volatile float *wF1=NULL,volatile float *wF2=NULL);
    MDS_AI_3RTD* addMDS_AI_3RTD(int addr,volatile float *rF1,volatile float *rF2,volatile float *rF3);
    MDS_DIO_44* addMDS_DIO_44(int addr,volatile bool *rB1=NULL,volatile bool *rB2=NULL,volatile bool *rB3=NULL,volatile bool *rB4=NULL,
        volatile bool *wB1=NULL,volatile bool *wB2=NULL,volatile bool *wB3=NULL,volatile bool *wB4=NULL);
    MDS_AIO_4* addMDS_AIO_4(int addr,
        volatile float *rF1=NULL,volatile float *rF2=NULL,volatile float *rF3=NULL,volatile float *rF4=NULL,
        volatile bool *rB1=NULL,volatile bool *rB2=NULL,volatile bool *rB3=NULL,volatile bool *rB4=NULL,
        volatile float *wF1=NULL,volatile float *wF2=NULL,volatile float *wF3=NULL,volatile float *wF4=NULL);
    void addTenzoM_TV006c(int address,volatile float *rF1, int rev=0);
    void addMicroMotion(int address,volatile float *massTotal);
    void addEmis_MAG_260(int addr, volatile float *rF);
    void addElemer_UR31(int addr, volatile float *rF);
    OWEN_MV110_8AS* addOWEN_MV110_8AS(int addr, volatile float *rR1=NULL,volatile float *rR2=NULL,volatile float *rR3=NULL,volatile float *rR4=NULL,
        volatile float *rR5=NULL,volatile float *rR6=NULL,volatile float *rR7=NULL,volatile float *rR8=NULL);
    OWEN_MV110_8A* addOWEN_MV110_8A(int addr, volatile float *rR1=NULL,volatile float *rR2=NULL,volatile float *rR3=NULL,volatile float *rR4=NULL,
        volatile float *rR5=NULL,volatile float *rR6=NULL,volatile float *rR7=NULL,volatile float *rR8=NULL);
    OWEN_MU110_8I* addOWEN_MU110_8I(int addr, volatile float *wR1=NULL,volatile float *wR2=NULL,volatile float *wR3=NULL,volatile float *wR4=NULL,
        volatile float *wR5=NULL,volatile float *wR6=NULL,volatile float *wR7=NULL,volatile float *wR8=NULL);
    OWEN_PLC110_60* addOWEN_PLC110_60(int address,
        volatile bool *rB1=NULL, volatile bool *rB2=NULL, volatile bool *rB3=NULL, volatile bool *rB4=NULL,
        volatile bool *rB5=NULL, volatile bool *rB6=NULL, volatile bool *rB7=NULL, volatile bool *rB8=NULL,
        volatile bool *rB9=NULL, volatile bool *rB10=NULL, volatile bool *rB11=NULL, volatile bool *rB12=NULL,
        volatile bool *rB13=NULL, volatile bool *rB14=NULL, volatile bool *rB15=NULL, volatile bool *rB16=NULL,
        volatile bool *rB17=NULL, volatile bool *rB18=NULL, volatile bool *rB19=NULL, volatile bool *rB20=NULL,
        volatile bool *rB21=NULL, volatile bool *rB22=NULL, volatile bool *rB23=NULL, volatile bool *rB24=NULL,
        volatile bool *rB25=NULL, volatile bool *rB26=NULL, volatile bool *rB27=NULL, volatile bool *rB28=NULL,
        volatile bool *rB29=NULL, volatile bool *rB30=NULL, volatile bool *rB31=NULL, volatile bool *rB32=NULL,
        volatile bool *rB33=NULL, volatile bool *rB34=NULL, volatile bool *rB35=NULL, volatile bool *rB36=NULL,
        volatile bool *wB1=NULL, volatile bool *wB2=NULL, volatile bool *wB3=NULL, volatile bool *wB4=NULL,
        volatile bool *wB5=NULL, volatile bool *wB6=NULL, volatile bool *wB7=NULL, volatile bool *wB8=NULL,
        volatile bool *wB9=NULL, volatile bool *wB10=NULL, volatile bool *wB11=NULL, volatile bool *wB12=NULL,
        volatile bool *wB13=NULL, volatile bool *wB14=NULL, volatile bool *wB15=NULL, volatile bool *wB16=NULL,
        volatile bool *wB17=NULL, volatile bool *wB18=NULL, volatile bool *wB19=NULL, volatile bool *wB20=NULL,
        volatile bool *wB21=NULL, volatile bool *wB22=NULL, volatile bool *wB23=NULL, volatile bool *wB24=NULL);
    OWEN_PLC160* addOWEN_PLC160(int addr,
        volatile bool *rB1=NULL,volatile bool *rB2=NULL,volatile bool *rB3=NULL,volatile bool *rB4=NULL,
        volatile bool *rB5=NULL,volatile bool *rB6=NULL,volatile bool *rB7=NULL,volatile bool *rB8=NULL,
        volatile bool *rB9=NULL,volatile bool *rB10=NULL,volatile bool *rB11=NULL,volatile bool *rB12=NULL,
        volatile bool *rB13=NULL,volatile bool *rB14=NULL,volatile bool *rB15=NULL,volatile bool *rB16=NULL,
        volatile float *rF1=NULL,volatile float *rF2=NULL,volatile float *rF3=NULL,volatile float *rF4=NULL,
        volatile float *rF5=NULL,volatile float *rF6=NULL,volatile float *rF7=NULL,volatile float *rF8=NULL,
        volatile float *rF9=NULL,
        volatile float *rC1=NULL,volatile float *rC2=NULL,volatile float *rC3=NULL,volatile float *rC4=NULL,
        volatile bool *wB1=NULL,volatile bool *wB2=NULL,volatile bool *wB3=NULL,volatile bool *wB4=NULL,
        volatile bool *wB5=NULL,volatile bool *wB6=NULL,volatile bool *wB7=NULL,volatile bool *wB8=NULL,
        volatile bool *wB9=NULL,volatile bool *wB10=NULL,volatile bool *wB11=NULL,volatile bool *wB12=NULL,
        volatile float *wF1=NULL,volatile float *wF2=NULL,volatile float *wF3=NULL,volatile float *wF4=NULL,
        volatile bool *wReset=NULL);
    Krohne_Optimass* addKrohne_Optimass(int addr, volatile double *rFQE=NULL, volatile float *rFQ=NULL, volatile float *rT=NULL, volatile float *rD=NULL);
    Delta_C2000* addDelta_C2000(int addr,volatile float *frq=NULL,volatile float *current=NULL,volatile bool *autostart=NULL,volatile bool *bStart=NULL,volatile bool *bStop=NULL,volatile bool *_state=NULL);
    Mettler_Toledo_IND570* addMettler_Toledo_IND570(int addr, volatile float *weight=NULL);
    ULM* addULM(int addr, volatile float *level=NULL);
protected:
    void Thread();

    modbus_t *ctx;
    long sleepTime;
    std::thread _t;
    bool _stop=false;

    std::vector<ModbusModule*> devices;
};

