#include "MDS-DIO-44.h"

MDS_DIO_44::MDS_DIO_44(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4)
        : rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},wB1{wB1},wB2{wB2},wB3{wB3},wB4{wB4},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[2];
    memset(buffer, 0, 2 * sizeof(uint16_t));
}
MDS_DIO_44::~MDS_DIO_44() {
    delete[] buffer;
}

void MDS_DIO_44::Write() {
    uint16_t temp=
        ((wB1==NULL)?0:(*wB1<<0))|
        ((wB2==NULL)?0:(*wB2<<1))|
        ((wB3==NULL)?0:(*wB3<<2))|
        ((wB4==NULL)?0:(*wB4<<3));
    buffer[1]=temp;
    Set();
    rc = modbus_write_register(ctx, 266, buffer[1]);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d MDS_DIO_44::Write() %s\n",address, modbus_strerror(errno));
}

void MDS_DIO_44::Read() {
    Set();
    rc = modbus_read_input_registers(ctx, 257, 1, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d MDS_DIO_44::Read() %s\n",address, modbus_strerror(errno));
    else {
        if(rB1!=NULL) *rB1=(buffer[0]>>0)&1;
        if(rB2!=NULL) *rB2=(buffer[0]>>1)&1;
        if(rB3!=NULL) *rB3=(buffer[0]>>2)&1;
        if(rB4!=NULL) *rB4=(buffer[0]>>3)&1;
    }
}
