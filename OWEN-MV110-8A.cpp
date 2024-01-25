#include "OWEN-MV110-8A.h"

OWEN_MV110_8A::OWEN_MV110_8A(modbus_t *ctx, int addr,
    volatile float *rR1,volatile float *rR2,volatile float *rR3,volatile float *rR4,volatile float *rR5,volatile float *rR6,volatile float *rR7,volatile float *rR8) 
    : rR1{rR1},rR2{rR2},rR3{rR3},rR4{rR4},rR5{rR5},rR6{rR6},rR7{rR7},rR8{rR8}, ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[48];
    memset(buffer, 0, 48 * sizeof(uint16_t));
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            lin[i][j]=0;

}
OWEN_MV110_8A::~OWEN_MV110_8A() {
    delete[] buffer;
}

void OWEN_MV110_8A::Read() {
    if(rR1==NULL && rR2==NULL && rR3==NULL && rR4==NULL && rR5==NULL && rR6==NULL && rR7==NULL && rR8==NULL) return;
    Set();
    rc = modbus_read_registers(ctx, 0, 48, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rR1!=NULL && buffer[2]==0) *rR1=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(buffer[1],lin[0][0],lin[0][1],lin[0][2],lin[0][3]):buffer[1];
        if(rR2!=NULL && buffer[8]==0) *rR2=(lin[1][0]!=0||lin[1][1]!=0||lin[1][2]!=0||lin[1][3]!=0)?flin2(buffer[7],lin[1][0],lin[1][1],lin[1][2],lin[1][3]):buffer[7];
        if(rR3!=NULL && buffer[14]==0) *rR3=(lin[2][0]!=0||lin[2][1]!=0||lin[2][2]!=0||lin[2][3]!=0)?flin2(buffer[13],lin[2][0],lin[2][1],lin[2][2],lin[2][3]):buffer[13];
        if(rR4!=NULL && buffer[20]==0) *rR4=(lin[3][0]!=0||lin[3][1]!=0||lin[3][2]!=0||lin[3][3]!=0)?flin2(buffer[19],lin[3][0],lin[3][1],lin[3][2],lin[3][3]):buffer[19];
        if(rR5!=NULL && buffer[26]==0) *rR5=(lin[4][0]!=0||lin[4][1]!=0||lin[4][2]!=0||lin[4][3]!=0)?flin2(buffer[25],lin[4][0],lin[4][1],lin[4][2],lin[4][3]):buffer[25];
        if(rR6!=NULL && buffer[32]==0) *rR6=(lin[5][0]!=0||lin[5][1]!=0||lin[5][2]!=0||lin[5][3]!=0)?flin2(buffer[31],lin[5][0],lin[5][1],lin[5][2],lin[5][3]):buffer[31];
        if(rR7!=NULL && buffer[38]==0) *rR7=(lin[6][0]!=0||lin[6][1]!=0||lin[6][2]!=0||lin[6][3]!=0)?flin2(buffer[37],lin[6][0],lin[6][1],lin[6][2],lin[6][3]):buffer[37];
        if(rR8!=NULL && buffer[44]==0) *rR8=(lin[7][0]!=0||lin[7][1]!=0||lin[7][2]!=0||lin[7][3]!=0)?flin2(buffer[43],lin[7][0],lin[7][1],lin[7][2],lin[7][3]):buffer[43];
    }
}
void OWEN_MV110_8A::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
