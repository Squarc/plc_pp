#include "MDS-AI-3RTD.h"

MDS_AI_3RTD::MDS_AI_3RTD(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3) 
        : rF1{rF1},rF2{rF2},rF3{rF3},ModbusModule(ctx,addr,setNullable){
    buffer = new uint16_t[6];
    memset(buffer, 0, 6 * sizeof(uint16_t));
}
MDS_AI_3RTD::~MDS_AI_3RTD() {
    delete[] buffer;
}

void MDS_AI_3RTD::Read() {
    Set();
    rc = modbus_read_registers(ctx, 279, 6, buffer);
    isError=(rc==-1);
    if (rc == -1)
        fprintf(stderr, "#%d MDS_AI_3RTD::Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rF1!=NULL) *rF1=modbus_get_float(buffer);
        if(rF2!=NULL) *rF2=modbus_get_float(buffer+2);
        if(rF3!=NULL) *rF3=modbus_get_float(buffer+4);
    }
}
