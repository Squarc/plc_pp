#include "OWEN-MV110-16DN.h"

OWEN_MV110_16DN::OWEN_MV110_16DN(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
        volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
        volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16) 
        : rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},rB5{rB5},rB6{rB6},rB7{rB7},rB8{rB8},
        rB9{rB9},rB10{rB10},rB11{rB11},rB12{rB12},rB13{rB13},rB14{rB14},rB15{rB15},rB16{rB16},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[1];
    memset(buffer, 0, 1 * sizeof(uint16_t));
}
OWEN_MV110_16DN::~OWEN_MV110_16DN() {
    delete[] buffer;
}

void OWEN_MV110_16DN::Read() {
    if(rB1==NULL&&rB2==NULL&&rB3==NULL&&rB4==NULL&&rB5==NULL&&rB6==NULL&&rB7==NULL&&rB8==NULL&&rB9==NULL&&rB10==NULL&&rB11==NULL&&rB12==NULL&&rB13==NULL&&rB14==NULL&&rB15==NULL&&rB16==NULL) return;
    Set();
    rc = modbus_read_input_registers(ctx, 51, 1, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rB1!=NULL) *rB1=(buffer[0]>>0)&1;
        if(rB2!=NULL) *rB2=(buffer[0]>>1)&1;
        if(rB3!=NULL) *rB3=(buffer[0]>>2)&1;
        if(rB4!=NULL) *rB4=(buffer[0]>>3)&1;
        if(rB5!=NULL) *rB5=(buffer[0]>>4)&1;
        if(rB6!=NULL) *rB6=(buffer[0]>>5)&1;
        if(rB7!=NULL) *rB7=(buffer[0]>>6)&1;
        if(rB8!=NULL) *rB8=(buffer[0]>>7)&1;
        if(rB9!=NULL) *rB9=(buffer[0]>>8)&1;
        if(rB10!=NULL) *rB10=(buffer[0]>>9)&1;
        if(rB11!=NULL) *rB11=(buffer[0]>>10)&1;
        if(rB12!=NULL) *rB12=(buffer[0]>>11)&1;
        if(rB13!=NULL) *rB13=(buffer[0]>>12)&1;
        if(rB14!=NULL) *rB14=(buffer[0]>>13)&1;
        if(rB15!=NULL) *rB15=(buffer[0]>>14)&1;
        if(rB16!=NULL) *rB16=(buffer[0]>>15)&1;
    }
}
