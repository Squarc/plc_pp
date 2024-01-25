#include "TenzoM_TV006c.h"
#include <iostream>
TenzoM_TV006c::TenzoM_TV006c(modbus_t *ctx, int addr, volatile float *rF1,
    int rev, bool setNullable) : rF1{rF1},rev{rev},ModbusModule(ctx,addr,setNullable){
    buffer = new uint16_t[2];
    memset(buffer, 0, 2 * sizeof(uint16_t));
}
TenzoM_TV006c::~TenzoM_TV006c() {
    delete[] buffer;
}

void TenzoM_TV006c::Read() {
    Set();
    if(rev==0) rc = modbus_read_registers(ctx, 307, 2, buffer);
    if(rev==1) rc = modbus_read_registers(ctx, 310, 2, buffer);
    if (rc == -1) {
        fprintf(stderr, "#%d TenzoM_TV006c::Read() %s\n",address, modbus_strerror(errno));
        isError=true;
    }
    else {
        if(rF1!=NULL) *rF1=modbus_get_float_badc(buffer);
        isError=false;
    }
}





