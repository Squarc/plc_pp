#include "MDS-AI-8UI.h"

MDS_AI_8UI::MDS_AI_8UI(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8) 
        : rF1{rF1},rF2{rF2},rF3{rF3},rF4{rF4},rF5{rF5},rF6{rF6},rF7{rF7},rF8{rF8},ModbusModule(ctx,addr,setNullable){
    buffer = new uint16_t[16];
    memset(buffer, 0, 16 * sizeof(uint16_t));
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            lin[i][j]=0;
}
MDS_AI_8UI::~MDS_AI_8UI() {
    delete[] buffer;
}

void MDS_AI_8UI::Read() {
    Set();
    rc = modbus_read_input_registers(ctx, 365, 16, buffer);
    isError=(rc==-1);
    if (rc == -1)
        fprintf(stderr, "#%d MDS_AI_8UI::Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rF1!=NULL) *rF1=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(modbus_get_float(buffer),lin[0][0],lin[0][1],lin[0][2],lin[0][3]):modbus_get_float(buffer);
        if(rF2!=NULL) *rF2=(lin[1][0]!=0||lin[1][1]!=0||lin[1][2]!=0||lin[1][3]!=0)?flin2(modbus_get_float(buffer+2),lin[1][0],lin[1][1],lin[1][2],lin[1][3]):modbus_get_float(buffer+2);
        if(rF3!=NULL) *rF3=(lin[2][0]!=0||lin[2][1]!=0||lin[2][2]!=0||lin[2][3]!=0)?flin2(modbus_get_float(buffer+4),lin[2][0],lin[2][1],lin[2][2],lin[2][3]):modbus_get_float(buffer+4);
        if(rF4!=NULL) *rF4=(lin[3][0]!=0||lin[3][1]!=0||lin[3][2]!=0||lin[3][3]!=0)?flin2(modbus_get_float(buffer+6),lin[3][0],lin[3][1],lin[3][2],lin[3][3]):modbus_get_float(buffer+6);
        if(rF5!=NULL) *rF5=(lin[4][0]!=0||lin[4][1]!=0||lin[4][2]!=0||lin[4][3]!=0)?flin2(modbus_get_float(buffer+8),lin[4][0],lin[4][1],lin[4][2],lin[4][3]):modbus_get_float(buffer+8);
        if(rF6!=NULL) *rF6=(lin[5][0]!=0||lin[5][1]!=0||lin[5][2]!=0||lin[5][3]!=0)?flin2(modbus_get_float(buffer+10),lin[5][0],lin[5][1],lin[5][2],lin[5][3]):modbus_get_float(buffer+10);
        if(rF7!=NULL) *rF7=(lin[6][0]!=0||lin[6][1]!=0||lin[6][2]!=0||lin[6][3]!=0)?flin2(modbus_get_float(buffer+12),lin[6][0],lin[6][1],lin[6][2],lin[6][3]):modbus_get_float(buffer+12);
        if(rF8!=NULL) *rF8=(lin[7][0]!=0||lin[7][1]!=0||lin[7][2]!=0||lin[7][3]!=0)?flin2(modbus_get_float(buffer+14),lin[7][0],lin[7][1],lin[7][2],lin[7][3]):modbus_get_float(buffer+14);
    }
}

void MDS_AI_8UI::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
