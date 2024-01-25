#include "OWEN-MV110-8AS.h"

OWEN_MV110_8AS::OWEN_MV110_8AS(modbus_t *ctx, int addr,
    volatile float *rR1,volatile float *rR2,volatile float *rR3,volatile float *rR4,volatile float *rR5,volatile float *rR6,volatile float *rR7,volatile float *rR8) 
    : rR1{rR1},rR2{rR2},rR3{rR3},rR4{rR4},rR5{rR5},rR6{rR6},rR7{rR7},rR8{rR8},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[8];
    memset(buffer, 0, 8 * sizeof(uint16_t));
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            lin[i][j]=0;

}
OWEN_MV110_8AS::~OWEN_MV110_8AS() {
    delete[] buffer;
}

void OWEN_MV110_8AS::Read() {
    if(rR1==NULL && rR2==NULL && rR3==NULL && rR4==NULL && rR5==NULL && rR6==NULL && rR7==NULL && rR8==NULL) return;
    Set();
    rc = modbus_read_registers(ctx, 256, 8, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rR1!=NULL) *rR1=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(buffer[0],lin[0][0],lin[0][1],lin[0][2],lin[0][3]):buffer[0];
        if(rR2!=NULL) *rR2=(lin[1][0]!=0||lin[1][1]!=0||lin[1][2]!=0||lin[1][3]!=0)?flin2(buffer[1],lin[1][0],lin[1][1],lin[1][2],lin[1][3]):buffer[1];
        if(rR3!=NULL) *rR3=(lin[2][0]!=0||lin[2][1]!=0||lin[2][2]!=0||lin[2][3]!=0)?flin2(buffer[2],lin[2][0],lin[2][1],lin[2][2],lin[2][3]):buffer[2];
        if(rR4!=NULL) *rR4=(lin[3][0]!=0||lin[3][1]!=0||lin[3][2]!=0||lin[3][3]!=0)?flin2(buffer[3],lin[3][0],lin[3][1],lin[3][2],lin[3][3]):buffer[3];
        if(rR5!=NULL) *rR5=(lin[4][0]!=0||lin[4][1]!=0||lin[4][2]!=0||lin[4][3]!=0)?flin2(buffer[4],lin[4][0],lin[4][1],lin[4][2],lin[4][3]):buffer[4];
        if(rR6!=NULL) *rR6=(lin[5][0]!=0||lin[5][1]!=0||lin[5][2]!=0||lin[5][3]!=0)?flin2(buffer[5],lin[5][0],lin[5][1],lin[5][2],lin[5][3]):buffer[5];
        if(rR7!=NULL) *rR7=(lin[6][0]!=0||lin[6][1]!=0||lin[6][2]!=0||lin[6][3]!=0)?flin2(buffer[6],lin[6][0],lin[6][1],lin[6][2],lin[6][3]):buffer[6];
        if(rR8!=NULL) *rR8=(lin[7][0]!=0||lin[7][1]!=0||lin[7][2]!=0||lin[7][3]!=0)?flin2(buffer[7],lin[7][0],lin[7][1],lin[7][2],lin[7][3]):buffer[7];
    }
}
void OWEN_MV110_8AS::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
