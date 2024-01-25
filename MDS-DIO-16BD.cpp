#include "MDS-DIO-16BD.h"

MDS_DIO_16BD::MDS_DIO_16BD(modbus_t *ctx, int addr,
    volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
    volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
    volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
    volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16,
    volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
    volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
    volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
    volatile bool *wB13,volatile bool *wB14,volatile bool *wB15,volatile bool *wB16,
    volatile uint16_t *rC1,volatile uint16_t *rC2,volatile uint16_t *rC3,volatile uint16_t *rC4,
    volatile bool *wReset1,volatile bool *wReset2,volatile bool *wReset3,volatile bool *wReset4) 
    : rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},rB5{rB5},rB6{rB6},rB7{rB7},rB8{rB8},
    rB9{rB9},rB10{rB10},rB11{rB11},rB12{rB12},rB13{rB13},rB14{rB14},rB15{rB15},rB16{rB16},
    wB1{wB1},wB2{wB2},wB3{wB3},wB4{wB4},wB5{wB5},wB6{wB6},wB7{wB7},wB8{wB8},
    wB9{wB9},wB10{wB10},wB11{wB11},wB12{wB12},wB13{wB13},wB14{wB14},wB15{wB15},wB16{wB16},
    rC1{rC1},rC2{rC2},rC3{rC3},rC4{rC4},
    wReset1{wReset1},wReset2{wReset2},wReset3{wReset3},wReset4{wReset4},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[16];
    memset(buffer, 0, 16 * sizeof(uint16_t));
    for(int i=0;i<16;i++) rev[i]=false;
}
MDS_DIO_16BD::~MDS_DIO_16BD() {
    delete[] buffer;
}

void MDS_DIO_16BD::Write() {
    uint16_t temp=0;
    if(wB1!=NULL||wB2!=NULL||wB3!=NULL||wB4!=NULL||wB5!=NULL||wB6!=NULL||wB7!=NULL||wB8!=NULL||
        wB9!=NULL||wB10!=NULL||wB11!=NULL||wB12!=NULL||wB13!=NULL||wB14!=NULL||wB15!=NULL||wB16!=NULL) {
        temp=((wB1==NULL)?0:rev[0]?!(*wB1<<0):(*wB1<<0))|
            ((wB2==NULL)?0:rev[1]?!(*wB2<<1):(*wB2<<1))|
            ((wB3==NULL)?0:rev[2]?!(*wB3<<2):(*wB3<<2))|
            ((wB4==NULL)?0:rev[3]?!(*wB4<<3):(*wB4<<3))|
            ((wB5==NULL)?0:rev[4]?!(*wB5<<4):(*wB5<<4))|
            ((wB6==NULL)?0:rev[5]?!(*wB6<<5):(*wB6<<5))|
            ((wB7==NULL)?0:rev[6]?!(*wB7<<6):(*wB7<<6))|
            ((wB8==NULL)?0:rev[7]?!(*wB8<<7):(*wB8<<7))|
            ((wB9==NULL)?0:rev[8]?!(*wB9<<8):(*wB9<<8))|
            ((wB10==NULL)?0:rev[9]?!(*wB10<<9):(*wB10<<9))|
            ((wB11==NULL)?0:rev[10]?!(*wB11<<10):(*wB11<<10))|
            ((wB12==NULL)?0:rev[11]?!(*wB12<<11):(*wB12<<11))|
            ((wB13==NULL)?0:rev[12]?!(*wB13<<12):(*wB13<<12))|
            ((wB14==NULL)?0:rev[13]?!(*wB14<<13):(*wB14<<13))|
            ((wB15==NULL)?0:rev[14]?!(*wB15<<14):(*wB15<<14))|
            ((wB16==NULL)?0:rev[15]?!(*wB16<<15):(*wB16<<15));
        //printf("#%d -> Write %d wB2=%d\n",address,temp,(wB2==NULL)?0:(*wB2<<1));
        buffer[1]=temp;
        Set();
        rc = modbus_write_registers(ctx, 267, 1, buffer+1);
        isError=(rc==-1);
        if (rc == -1)
            fprintf(stderr, "#%d MDS_DIO_16BD::Write(... %s\n", address, modbus_strerror(errno));
    }
    if(wReset1!=NULL||wReset2!=NULL||wReset3!=NULL||wReset4!=NULL) {
        temp=((wReset1==NULL)?0:(*wReset1<<0))|
            ((wReset2==NULL)?0:(*wReset2<<1))|
            ((wReset3==NULL)?0:(*wReset3<<2))|
            ((wReset4==NULL)?0:(*wReset4<<3));

        rc = modbus_write_register(ctx, 276, temp);
        isError&=(rc==-1);
        if (rc == -1)
            fprintf(stderr, "#%d MDS_DIO_16BD::Write(... %s\n",address, modbus_strerror(errno));
    }
}

void MDS_DIO_16BD::Read() {
    if(rB1!=NULL||rB2!=NULL||rB3!=NULL||rB4!=NULL||rB5!=NULL||rB6!=NULL||rB7!=NULL||rB8!=NULL||
        rB9!=NULL||rB10!=NULL||rB11!=NULL||rB12!=NULL||rB13!=NULL||rB14!=NULL||rB15!=NULL||rB16!=NULL) {
        Set();
        rc = modbus_read_registers(ctx, 258, 1, buffer);
        isError=(rc==-1);
        if (rc == -1)
            fprintf(stderr, "#%d MDS_DIO_16BD::Read() %s\n",address, modbus_strerror(errno));
        else {
            if(rB1!=NULL) *rB1=(buffer[0]>>0)&1;
            if(rB2!=NULL) *rB2=(buffer[0]>>1)&1;
            if(rB3!=NULL) *rB3=(buffer[0]>>2)&1;
            if(rB4!=NULL) *rB4=(buffer[0]>>3)&1;
            if(rB5!=NULL) *rB5=(buffer[0]>>4)&1;
            if(rB6!=NULL) *rB6=(buffer[0]>>5)&1;
            if(rB7!=NULL) *rB7=(buffer[0]>>6)&1;
            if(rB8!=NULL) *rB8=(buffer[0]>>7)&1;
            if(rB9!=NULL) *rB9=(buffer[0]>>8)&1;
            if(rB10!=NULL) *rB10=(buffer[0]>>9)&1;
            if(rB11!=NULL) *rB11=(buffer[0]>>10)&1;
            if(rB12!=NULL) *rB12=(buffer[0]>>11)&1;
            if(rB13!=NULL) *rB13=(buffer[0]>>12)&1;
            if(rB14!=NULL) *rB14=(buffer[0]>>13)&1;
            if(rB15!=NULL) *rB15=(buffer[0]>>14)&1;
            if(rB16!=NULL) *rB16=(buffer[0]>>15)&1;
        }
    }
    if(rC1!=NULL||rC2!=NULL||rC3!=NULL||rC4!=NULL) {
        rc = modbus_read_registers(ctx, 278, 4, buffer);
        isError&=(rc==-1);
        if (rc == -1)
            fprintf(stderr, "#%d MDS_DIO_16BD::Read() %s\n",address, modbus_strerror(errno));
        else {
            if(rC1!=NULL) *rC1=buffer[0];
            if(rC2!=NULL) *rC2=buffer[1];
            if(rC3!=NULL) *rC3=buffer[2];
            if(rC4!=NULL) *rC4=buffer[3];
        }
    }
}

void MDS_DIO_16BD::setRev(int index) {
    if(index<0 || index>15) return;
    rev[index]=!rev[index];
}