#include "Krohne_Optimass.h"

Krohne_Optimass::Krohne_Optimass(modbus_t *ctx, int addr, volatile double *rFQE, volatile float *rFQ, volatile float *rT, volatile float *rD) :
    rFQE{rFQE},rFQ{rFQ},rT{rT},rD{rD}, ModbusModule(ctx,addr,setNullable){
    buffer = new uint16_t[6];
    memset(buffer, 0, 6 * sizeof(uint16_t));
}
Krohne_Optimass::~Krohne_Optimass() {
    delete[] buffer;
}
void Krohne_Optimass::Read() {
    if(rFQE!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 2000, 4, buffer);
        isError=(rc==-1);
        if (rc == -1) fprintf(stderr, "#%d Krohne_Optimass::Read FQE %s\n",address, modbus_strerror(errno));
        else {
            uint16_t t=buffer[3];
            buffer[3]=buffer[0];
            buffer[0]=t;
            t=buffer[2];
            buffer[2]=buffer[1];
            buffer[1]=t;
            *rFQE=((double*)buffer)[0];
        }
    }
    nsleep(50);
    if(rFQ!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 4, 6, buffer);
        isError&=(rc==-1);
        if (rc == -1) fprintf(stderr, "#%d Krohne_Optimass::Read FQ,T,D %s\n",address, modbus_strerror(errno));
        else {
            *rFQ=modbus_get_float_dcba(buffer);
            *rT=modbus_get_float_dcba(buffer+2)-273.15;
            *rD=modbus_get_float_dcba(buffer+4);
        }
    }
    nsleep(50);
}

