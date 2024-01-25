#include "OWEN-MK110-8D-4R.h"

OWEN_MK110_8D_4R::OWEN_MK110_8D_4R(modbus_t *ctx, int addr,
    volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
    volatile float *wR1,volatile float *wR2,volatile float *wR3,volatile float *wR4,
    bool setNullable) : 
    rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},
    wR1{wR1},wR2{wR2},wR3{wR3},wR4{wR4},
    ModbusModule(ctx,addr,setNullable) {
    buffer = new uint16_t[5];
    memset(buffer, 0, 5 * sizeof(uint16_t));
}
OWEN_MK110_8D_4R::~OWEN_MK110_8D_4R() {
    delete[] buffer;
}

void OWEN_MK110_8D_4R::Write() {
    if(wR1==NULL && wR2==NULL && wR3==NULL && wR4==NULL) return;
    Set();
    memset(buffer, 0, 5 * sizeof(uint16_t));
    if(wR1!=NULL) buffer[1]=*wR1;
    if(wR2!=NULL) buffer[2]=*wR2;
    if(wR3!=NULL) buffer[3]=*wR3;
    if(wR4!=NULL) buffer[4]=*wR4;
    Set();
    rc = modbus_write_registers(ctx, 0,4, buffer+1);
    isError=(rc==-1);
    if (rc == -1)
        fprintf(stderr, "#%d Write(uint16_t v1, uint16_t v2, uint16_t v3, uint16_t v4) %s\n",address, modbus_strerror(errno));
}

void OWEN_MK110_8D_4R::Read() {
    if(rB1==NULL && rB2==NULL && rB3==NULL && rB4==NULL) return;
    Set();
    if(setNullable) memset(buffer, 0, 5 * sizeof(uint16_t));
    rc = modbus_read_input_registers(ctx, 51, 1, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rB1!=NULL) *rB1=(buffer[0]>>0)&1;
        if(rB2!=NULL) *rB2=(buffer[0]>>1)&1;
        if(rB3!=NULL) *rB3=(buffer[0]>>2)&1;
        if(rB4!=NULL) *rB4=(buffer[0]>>3)&1;
    }
}
