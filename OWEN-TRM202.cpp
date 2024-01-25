#include "OWEN-TRM202.h"

OWEN_TRM202::OWEN_TRM202(modbus_t *ctx, int addr,
    volatile float *rF1,volatile float *rF2) : rF1{rF1},rF2{rF2},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[4];
    memset(buffer, 0, 4 * sizeof(uint16_t));
}
OWEN_TRM202::~OWEN_TRM202() {
    delete[] buffer;
}

void OWEN_TRM202::Read() {
    Set();
    rc = modbus_read_registers(ctx, 0x1009, 4, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d:%x Read() %s\n",address,0x1009, modbus_strerror(errno));
    else {
        if(rF1!=NULL) modbus_get_float_dcba(buffer);
        if(rF2!=NULL) modbus_get_float_dcba(buffer+2);
    }
}
