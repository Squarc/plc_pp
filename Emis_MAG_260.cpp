#include "Emis_MAG_260.h"
#include <iostream>

Emis_MAG_260::Emis_MAG_260(modbus_t *ctx, int addr, volatile float *rF) :
    rF{rF}, ModbusModule(ctx,addr,false){
    buffer = new uint16_t[4];
    memset(buffer, 0, 4 * sizeof(uint16_t));
    buffer[0]=buffer[2]=0;
}
Emis_MAG_260::~Emis_MAG_260() {
    delete[] buffer;
}

void Emis_MAG_260::Read() {
    if(rF!=NULL) {
        Set();
        rc = modbus_read_registers(ctx, 175, 2, buffer);
        isError=(rc==-1);
        if (rc == -1) fprintf(stderr, "#%d Emis_MAG_260::Read() %s\n",address, modbus_strerror(errno));
        else {*rF=modbus_get_float_dcba(buffer);
            //std::cout<<"Emis "<<*rF<<std::endl;
        }
    }
}

