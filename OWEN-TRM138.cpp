#include "OWEN-TRM138.h"

OWEN_TRM138::OWEN_TRM138(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8
    ) : rF1{rF1},rF2{rF2},rF3{rF3},rF4{rF4},rF5{rF5},rF6{rF6},rF7{rF7},rF8{rF8},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[40];
    memset(buffer, 0, 40 * sizeof(uint16_t));
}
OWEN_TRM138::~OWEN_TRM138() {
    delete[] buffer;
}

void OWEN_TRM138::Read() {
    Set();
    rc = modbus_read_input_registers(ctx, 0, 40, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rF1!=NULL) *rF1=modbus_get_float_dcba(buffer+3);
        if(rF2!=NULL) *rF2=modbus_get_float_dcba(buffer+8);
        if(rF3!=NULL) *rF3=modbus_get_float_dcba(buffer+13);
        if(rF4!=NULL) *rF4=modbus_get_float_dcba(buffer+18);
        if(rF5!=NULL) *rF5=modbus_get_float_dcba(buffer+23);
        if(rF6!=NULL) *rF6=modbus_get_float_dcba(buffer+28);
        if(rF7!=NULL) *rF7=modbus_get_float_dcba(buffer+33);
        if(rF8!=NULL) *rF8=modbus_get_float_dcba(buffer+38);
    }

}
