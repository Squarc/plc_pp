#include "ULM.h"

ULM::ULM(modbus_t *ctx, int addr, volatile float *level):level{level}, ModbusModule(ctx,addr,false){
    buffer = new uint16_t[2];
    memset(buffer, 0, 2 * sizeof(uint16_t));
    oldValue=-1;
}
ULM::~ULM() {
    delete[] buffer;
}

void ULM::Read() {
    if(level!=NULL) {
        Set();
        rc = modbus_read_input_registers(ctx, 0, 2, buffer);
        if (rc == -1) {
            fprintf(stderr, "#%d ULM::Read() %s\n",address, modbus_strerror(errno));
            errorCount++;
            if(errorCount>100) errorCount=100;
        }
        else errorCount=0;
        isError=(errorCount>3);
        isChanged=(oldIsError!=isError);
        oldIsError=isError;
        if (rc == -1) *level= oldValue;
        oldValue=((float)buffer[0]*65536.0+(float)buffer[1])/10.0;
        *level=  oldValue;
    }
}

