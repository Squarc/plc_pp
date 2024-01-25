//#define DEBUG
#include "MicroMotion.h"

MicroMotion::MicroMotion(modbus_t *ctx, int addr, volatile float *massTotal, bool setNullable) : massTotal{massTotal}, ModbusModule(ctx,addr,setNullable){
    buffer = new uint16_t[2];
    memset(buffer, 0, 2 * sizeof(uint16_t));
}
MicroMotion::~MicroMotion() {
    delete[] buffer;
}

void MicroMotion::Read() {
    if(massTotal!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 259, 2, buffer);
        isError=(rc==-1);
        if (rc == -1)
            fprintf(stderr, "#%d MicroMotion::Read() %s\n",address, modbus_strerror(errno));
        else
            *massTotal = modbus_get_float_badc(buffer);
    }
}

void MicroMotion::Write() { }




