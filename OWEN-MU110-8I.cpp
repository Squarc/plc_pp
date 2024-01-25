#include "OWEN-MU110-8I.h"

OWEN_MU110_8I::OWEN_MU110_8I(modbus_t *ctx, int addr,
        volatile float *wR1,volatile float *wR2,volatile float *wR3,volatile float *wR4,
        volatile float *wR5,volatile float *wR6,volatile float *wR7,volatile float *wR8):
        wR1{wR1},wR2{wR2},wR3{wR3},wR4{wR4},wR5{wR5},wR6{wR6},wR7{wR7},wR8{wR8},
        ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[8];
    memset(buffer, 0, 8 * sizeof(uint16_t));
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            lin[i][j]=0;

}

OWEN_MU110_8I::~OWEN_MU110_8I() {
    delete[] buffer;
}

void OWEN_MU110_8I::Write() {
    if(wR1==NULL && wR2==NULL && wR3==NULL && wR4==NULL && 
        wR5==NULL && wR6==NULL && wR7==NULL && wR8==NULL) return;
    if(wR1!=NULL) buffer[0]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR1,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR1;
    if(wR2!=NULL) buffer[1]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR2,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR2;
    if(wR3!=NULL) buffer[2]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR3,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR3;
    if(wR4!=NULL) buffer[3]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR4,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR4;
    if(wR5!=NULL) buffer[4]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR5,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR5;
    if(wR6!=NULL) buffer[5]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR6,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR6;
    if(wR7!=NULL) buffer[6]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR7,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR7;
    if(wR8!=NULL) buffer[7]=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wR8,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wR8;
    Set();
    rc=modbus_write_registers(ctx,0,8,buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Write(... %s\n", address, modbus_strerror(errno));
}

void OWEN_MU110_8I::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
