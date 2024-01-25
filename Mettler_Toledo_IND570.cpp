#include "Mettler_Toledo_IND570.h"

Mettler_Toledo_IND570::Mettler_Toledo_IND570(modbus_t *ctx, int addr, volatile float *weight):weight{weight}, ModbusModule(ctx,addr,false){
    buffer = new uint16_t[4];
    memset(buffer, 0, 4 * sizeof(uint16_t));
    oldValue=-1;
}
Mettler_Toledo_IND570::~Mettler_Toledo_IND570() {
    delete[] buffer;
}

void Mettler_Toledo_IND570::Read() {
    if(weight!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 0, 3, buffer);
        if (rc == -1) {
            fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno));
            errorCount++;
            if(errorCount>100) errorCount=100;
        }
        else errorCount=0;
        isError=(errorCount>3);
        isChanged=(oldIsError!=isError);
        oldIsError=isError;
        if (rc == -1) *weight= oldValue;
        oldValue=modbus_get_float_abcd(buffer+1);
        *weight=  oldValue;
    }
}

