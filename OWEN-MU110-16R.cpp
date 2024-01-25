#include "OWEN-MU110-16R.h"

OWEN_MU110_16R::OWEN_MU110_16R(modbus_t *ctx, int addr,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
        volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
        volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
        volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16) :
        wB1{wB1},wB2{wB2},wB3{wB3},wB4{wB4},wB5{wB5},wB6{wB6},wB7{wB7},wB8{wB8},
        wB9{wB9},wB10{wB10},wB11{wB11},wB12{wB12},wB13{wB13},wB14{wB14},wB15{wB15},wB16{wB16},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[1];
    memset(buffer, 0, 1 * sizeof(uint16_t));
}
OWEN_MU110_16R::~OWEN_MU110_16R() {
    delete[] buffer;
}

void OWEN_MU110_16R::Write() {
    buffer[0]=((wB1==NULL)?0:((*wB1^r1)<<0))|
        ((wB2==NULL)?0:((*wB2^r2)<<0))|
        ((wB3==NULL)?0:((*wB3^r3)<<0))|
        ((wB4==NULL)?0:((*wB4^r4)<<0))|
        ((wB5==NULL)?0:((*wB5^r5)<<0))|
        ((wB6==NULL)?0:((*wB6^r6)<<0))|
        ((wB7==NULL)?0:((*wB7^r7)<<0))|
        ((wB8==NULL)?0:((*wB8^r8)<<0))|
        ((wB9==NULL)?0:((*wB9^r9)<<0))|
        ((wB10==NULL)?0:((*wB10^r10)<<0))|
        ((wB11==NULL)?0:((*wB11^r11)<<0))|
        ((wB12==NULL)?0:((*wB12^r12)<<0))|
        ((wB13==NULL)?0:((*wB13^r13)<<0))|
        ((wB14==NULL)?0:((*wB14^r14)<<0))|
        ((wB15==NULL)?0:((*wB15^r15)<<0))|
        ((wB16==NULL)?0:((*wB16^r16)<<0));
    Set();
    rc=modbus_write_registers(ctx,50,1,buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Write(... %s\n", address, modbus_strerror(errno));
}
void OWEN_MU110_16R::setReverse(int index) {
    if(index==0) r1=true;
    if(index==1) r2=true;
    if(index==2) r3=true;
    if(index==3) r4=true;
    if(index==4) r5=true;
    if(index==5) r6=true;
    if(index==6) r7=true;
    if(index==7) r8=true;
    if(index==8) r9=true;
    if(index==9) r10=true;
    if(index==10) r11=true;
    if(index==11) r12=true;
    if(index==12) r13=true;
    if(index==13) r14=true;
    if(index==14) r15=true;
    if(index==15) r16=true;
}



