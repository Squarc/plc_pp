#include "Elemer_UR31.h"

Elemer_UR31::Elemer_UR31(modbus_t *ctx, int addr, volatile float *rF) :
    rF{rF}, ModbusModule(ctx,addr,false){
    buffer = new uint16_t[4];
    memset(buffer, 0, 4 * sizeof(uint16_t));
    buffer[0]=0;
}
Elemer_UR31::~Elemer_UR31() {
    delete[] buffer;
}

void Elemer_UR31::Read() {
    if(rF!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 0, 1, buffer);
        isError=(rc==-1);
        if (rc == -1) fprintf(stderr, "#%d Elemer_UR31::ReadRegister() %s\n",address, modbus_strerror(errno));
        else {
            *rF=buffer[0];
        }
    }
    nsleep(50);
}

