#include "ModbusLine.h"



ModbusLine::ModbusLine(modbus_t *ctx, long sleepTime) : ctx{ctx},sleepTime{sleepTime} {
    _t=std::thread(&ModbusLine::Thread,this);
    printf("ModbusLine create\n");
}
ModbusLine::~ModbusLine() {
    _stop=true;
    _t.join();
    for(auto& dev:devices) delete dev;
    devices.clear();
    modbus_close(ctx);
    modbus_free(ctx);
    printf("ModbusLine delete\n");
}

void ModbusLine::Thread() {
    fflush(stdout);
    int isOpen=-1;
    auto olderrno=errno;
    while(!_stop) {
        if (isOpen==-1) {
            cout<<"Try open port..."<<endl;
			if ((isOpen = modbus_connect(ctx)) == -1) {
				if(errno!=olderrno) {
                    fprintf(stderr, "Connection failed: %s\n",modbus_strerror(errno));
                }
                modbus_close(ctx);
				modbus_free(ctx);
                
			} else {
                modbus_set_error_recovery(ctx,  (modbus_error_recovery_mode)6);
                modbus_set_response_timeout(ctx, 1,1000);
            }
            olderrno=errno;
            nsleep(1000);
			continue;
        }

        bool err=true;
        for(auto& dev:devices) {
            dev->Read();
            if(dev->isError==false) err=false;
            nsleep(50);
            dev->Write();
            if(dev->isError==false) err=false;
            nsleep(50);
        }
        if(err) {

            isOpen=-1;
			//modbus_free(ctx);
        }
        nsleep(sleepTime);
    }
}

void ModbusLine::addOWEN_TRM138(int address,volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8) {
    devices.push_back((ModbusModule*)new OWEN_TRM138(ctx,address,rF1,rF2,rF3,rF4,rF5,rF6,rF7,rF8));
}
void ModbusLine::addOWEN_TRM202(int address,volatile float *rF1,volatile float *rF2) {
    devices.push_back((ModbusModule*)new OWEN_TRM202(ctx,address,rF1,rF2));
}
MDS_AI_8UI* ModbusLine::addMDS_AI_8UI(int address,
    volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
    volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8) {
    auto out = new MDS_AI_8UI(ctx,address,rF1,rF2,rF3,rF4,rF5,rF6,rF7,rF8);
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_DIO_16BD* ModbusLine::addMDS_DIO_16BD(int address,
    volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
    volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
    volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
    volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16,
    volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
    volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
    volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
    volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16,
    volatile uint16_t *rC1,volatile uint16_t *rC2,volatile uint16_t *rC3,volatile uint16_t *rC4,
    volatile bool *wReset1,volatile bool *wReset2,volatile bool *wReset3,volatile bool *wReset4) {
    auto out = new MDS_DIO_16BD(ctx,address,rB1,rB2,rB3,rB4,
        rB5,rB6,rB7,rB8,rB9,rB10,rB11,rB12,rB13,rB14,rB15,rB16,
        wB1,wB2,wB3,wB4,wB5,wB6,wB7,wB8,wB9,wB10,wB11,wB12,wB13,wB14,wB15,wB16,
        rC1,rC2,rC3,rC4,wReset1,wReset2,wReset3,wReset4); 
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_DIO_16BD* ModbusLine::addMDS_DIO_16BD_W(int address,
    volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
    volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
    volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
    volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16,
    volatile uint16_t *rC1,volatile uint16_t *rC2,volatile uint16_t *rC3,volatile uint16_t *rC4,
    volatile bool *wReset1,volatile bool *wReset2,volatile bool *wReset3,volatile bool *wReset4) {
    auto out = new MDS_DIO_16BD(ctx,address,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        wB1,wB2,wB3,wB4,wB5,wB6,wB7,wB8,wB9,wB10,wB11,wB12,wB13,wB14,wB15,wB16,
        rC1,rC2,rC3,rC4,wReset1,wReset2,wReset3,wReset4); 
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_AO_2UI* ModbusLine::addMDS_AO_2UI(int addr,volatile float *wF1,volatile float *wF2) {
    auto out = new MDS_AO_2UI(ctx,addr,wF1,wF2); 
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_AI_3RTD* ModbusLine::addMDS_AI_3RTD(int addr,volatile float *rF1,volatile float *rF2,volatile float *rF3){
    auto out = new MDS_AI_3RTD(ctx,addr,rF1,rF2,rF3); 
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_DIO_44* ModbusLine::addMDS_DIO_44(int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4){
    auto out = new MDS_DIO_44(ctx,addr,rB1,rB2,rB3,rB4,
        wB1,wB2,wB3,wB4); 
    devices.push_back((ModbusModule*)out);
    return out;
}
MDS_AIO_4* ModbusLine::addMDS_AIO_4(int addr,
    volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
    volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile float *wF1,volatile float *wF2,volatile float *wF3,volatile float *wF4) {
    auto out=new MDS_AIO_4(ctx,addr,
        rF1,rF2,rF3,rF4,rB1,rB2,rB3,rB4,wF1,wF2,wF3,wF4);
    devices.push_back((ModbusModule*)out);
    return out;
}

void ModbusLine::addTenzoM_TV006c(int address,volatile float *rF1, int rev) {
    devices.push_back((ModbusModule*)new TenzoM_TV006c(ctx,address,rF1,rev));
}
void ModbusLine::addMicroMotion(int address,volatile float *massTotal) {
    devices.push_back((ModbusModule*)new MicroMotion(ctx,address,massTotal));
}
void ModbusLine::addEmis_MAG_260(int addr, volatile float *rF) {
    devices.push_back((ModbusModule*)new Emis_MAG_260(ctx,addr,rF));
}
void ModbusLine::addElemer_UR31(int addr, volatile float *rF) {
    devices.push_back((ModbusModule*)new Elemer_UR31(ctx,addr,rF));
}
Krohne_Optimass* ModbusLine::addKrohne_Optimass(int addr, volatile double *rFQE, volatile float *rFQ, volatile float *rT, volatile float *rD) {
    auto out = new Krohne_Optimass(ctx,addr,rFQE,rFQ,rT,rD); 
    devices.push_back((ModbusModule*)out);
    return out;
}
void ModbusLine::addOWEN_MV110_16DN(int address,volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
    volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
    volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
    volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16) {
    devices.push_back((ModbusModule*)new OWEN_MV110_16DN(ctx,address,rB1,rB2,rB3,rB4,rB5,rB6,rB7,rB8,rB9,rB10,rB11,rB12,rB13,rB14,rB15,rB16));
}
OWEN_MU110_16R* ModbusLine::addOWEN_MU110_16R(int address,
    volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
    volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
    volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
    volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16) {
    devices.push_back((ModbusModule*)new OWEN_MU110_16R(ctx,address,wB1,wB2,wB3,wB4,wB5,wB6,wB7,wB8,wB9,wB10,wB11,wB12,wB13,wB14,wB15,wB16));
}
OWEN_MV110_8AS* ModbusLine::addOWEN_MV110_8AS(int addr, volatile float *rR1,volatile float *rR2,volatile float *rR3,volatile float *rR4,volatile float *rR5,volatile float *rR6,volatile float *rR7,volatile float *rR8) {
    auto out=new OWEN_MV110_8AS(ctx, addr, rR1,rR2,rR3,rR4,rR5,rR6,rR7,rR8);
    devices.push_back((ModbusModule*)out);
    return out;
}
OWEN_MV110_8A* ModbusLine::addOWEN_MV110_8A(int addr, volatile float *rR1,volatile float *rR2,volatile float *rR3,volatile float *rR4,volatile float *rR5,volatile float *rR6,volatile float *rR7,volatile float *rR8) {
    auto out=new OWEN_MV110_8A(ctx, addr, rR1,rR2,rR3,rR4,rR5,rR6,rR7,rR8);
    devices.push_back((ModbusModule*)out);
    return out;
}
OWEN_MU110_8I* ModbusLine::addOWEN_MU110_8I(int addr, volatile float *wR1,volatile float *wR2,volatile float *wR3,volatile float *wR4,
    volatile float *wR5,volatile float *wR6,volatile float *wR7,volatile float *wR8) {
    auto out=new OWEN_MU110_8I(ctx, addr, wR1,wR2,wR3,wR4,wR5,wR6,wR7,wR8);
    devices.push_back((ModbusModule*)out);
    return out;
}

OWEN_PLC110_60* ModbusLine::addOWEN_PLC110_60(int address,
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
    volatile bool *wB21, volatile bool *wB22, volatile bool *wB23, volatile bool *wB24) {
    auto out=new OWEN_PLC110_60(ctx,address,
        rB1,rB2,rB3,rB4,rB5,rB6,rB7,rB8,rB9,rB10,rB11,rB12,rB13,rB14,rB15,rB16,
        rB17,rB18,rB19,rB20,rB21,rB22,rB23,rB24,rB25,rB26,rB27,rB28,rB29,rB30,rB31,rB32,
        rB33,rB34,rB35,rB36,
        wB1,wB2,wB3,wB4,wB5,wB6,wB7,wB8,wB9,wB10,wB11,wB12,wB13,wB14,wB15,wB16,
        wB17,wB18,wB19,wB20,wB21,wB22,wB23,wB24);
    devices.push_back((ModbusModule*)out);
    return out;
}
OWEN_PLC160* ModbusLine::addOWEN_PLC160(int addr,
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
        volatile bool *wReset) {
    auto out=new OWEN_PLC160(ctx,addr,
        rB1,rB2,rB3,rB4,rB5,rB6,rB7,rB8,rB9,rB10,rB11,rB12,rB13,rB14,rB15,rB16,
        rF1,rF2,rF3,rF4,rF5,rF6,rF7,rF8,rF9,
        rC1,rC2,rC3,rC4,
        wB1,wB2,wB3,wB4,wB5,wB6,wB7,wB8,wB9,wB10,wB11,wB12,
        wF1,wF2,wF3,wF4,
        wReset);
    devices.push_back((ModbusModule*)out);
    return out;
}
Delta_C2000* ModbusLine::addDelta_C2000(int addr,volatile float *frq,volatile float *current,volatile bool *autostart,volatile bool *bStart,volatile bool *bStop,volatile bool *_state){
    auto out=new Delta_C2000(ctx,addr,frq,current,autostart,bStart,bStop,_state);
    devices.push_back((ModbusModule*)out);
    return out;
}
Mettler_Toledo_IND570* ModbusLine::addMettler_Toledo_IND570(int addr, volatile float *weight) {
    auto out=new Mettler_Toledo_IND570(ctx,addr,weight);
    devices.push_back((ModbusModule*)out);
    return out;
}
ULM* ModbusLine::addULM(int addr, volatile float *level) {
    auto out=new ULM(ctx,addr,level);
    devices.push_back((ModbusModule*)out);
    return out;
}
