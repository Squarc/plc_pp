#include "MDS-AO-2UI.h"
#include <iostream>

MDS_AO_2UI::MDS_AO_2UI(modbus_t *ctx, int addr,
        volatile float *wF1,volatile float *wF2) : wF1{wF1},wF2{wF2}, ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[4];
    memset(buffer, 0, 4 * sizeof(uint16_t));
}
MDS_AO_2UI::~MDS_AO_2UI() {
    delete[] buffer;
}

void MDS_AO_2UI::Write() {
    Set();
    if(wF1!=NULL) {
        modbus_set_float_badc((lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(*wF1,lin[0][0],lin[0][1],lin[0][2],lin[0][3]):*wF1,buffer);
        rc = modbus_write_registers(ctx, 263, 2, buffer);
        isError=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d MDS_AO_2UI::Write() %s\n",address, modbus_strerror(errno));
    }
    if(wF2!=NULL) {
        modbus_set_float_badc((lin[1][0]!=0||lin[1][1]!=0||lin[1][2]!=0||lin[1][3]!=0)?flin2(*wF2,lin[1][0],lin[1][1],lin[1][2],lin[1][3]):*wF2,buffer+2);
        rc = modbus_write_registers(ctx, 277, 2, buffer+2);
        isError|=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d MDS_AO_2UI::Write() %s\n",address, modbus_strerror(errno));
    }
}

void MDS_AO_2UI::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
