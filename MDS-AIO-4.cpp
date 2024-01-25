#include "MDS-AIO-4.h"

MDS_AIO_4::MDS_AIO_4(modbus_t *ctx, int addr,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile float *wF1,volatile float *wF2,volatile float *wF3,volatile float *wF4)
        : rF1{rF1},rF2{rF2},rF3{rF3},rF4{rF4},
        rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},
        wF1{wF1},wF2{wF2},wF3{wF3},wF4{wF4},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[9];
    memset(buffer, 0, 9 * sizeof(uint16_t));
    rev[0]=rev[1]=rev[2]=rev[3]=false;
}
MDS_AIO_4::~MDS_AIO_4() {
    delete[] buffer;
}

void MDS_AIO_4::Read() {
    Set();
    if(rF1!=NULL||rF2!=NULL||rF3!=NULL||rF4!=NULL) {
        rc = modbus_read_input_registers(ctx, 207, 8, buffer);
        isError=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d MDS_AIO_4::Read() %s\n", modbus_strerror(errno));
        else {
            if(rF1!=NULL) *rF1=modbus_get_float_badc(buffer);
            if(rF2!=NULL) *rF2=modbus_get_float_badc(buffer+2);
            if(rF3!=NULL) *rF3=modbus_get_float_badc(buffer+4);
            if(rF4!=NULL) *rF4=modbus_get_float_badc(buffer+6);
        }
    }
    if(rB1!=NULL||rB2!=NULL||rB3!=NULL||rB4!=NULL) {
        rc = modbus_read_input_registers(ctx, 186, 1, buffer+8);
        isError&=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "%s\n", modbus_strerror(errno));
        else {
            if(rB1!=NULL) *rB1=(buffer[8]<<0)&1;
            if(rB2!=NULL) *rB2=(buffer[8]<<1)&1;
            if(rB3!=NULL) *rB3=(buffer[8]<<2)&1;
            if(rB4!=NULL) *rB4=(buffer[8]<<3)&1;
        }
    }
}

void MDS_AIO_4::Write() {
    Set();
    if(wF1!=NULL||wF2!=NULL||wF3!=NULL||wF4!=NULL) {
        modbus_set_float_badc(wF1==NULL?0:(rev[0]?100-*wF1:*wF1),buffer);
        modbus_set_float_badc(wF2==NULL?0:(rev[1]?100-*wF2:*wF2),buffer+2);
        modbus_set_float_badc(wF3==NULL?0:(rev[2]?100-*wF3:*wF3),buffer+4);
        modbus_set_float_badc(wF4==NULL?0:(rev[3]?100-*wF4:*wF4),buffer+6);

        modbus_write_registers(ctx,267,4*sizeof(float),buffer);
        isError=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d MDS_AIO_4::Write() %s\n", modbus_strerror(errno));
    }
}

void MDS_AIO_4::setReverce(int index) {
    if(index<0|| index>4) return;
    rev[index]=!rev[index];

}
