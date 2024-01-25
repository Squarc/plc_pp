#include "OWEN-PLC160.h"

OWEN_PLC160::OWEN_PLC160(modbus_t *ctx, int addr,
        volatile bool *rB1,volatile bool *rB2,volatile bool *rB3,volatile bool *rB4,
        volatile bool *rB5,volatile bool *rB6,volatile bool *rB7,volatile bool *rB8,
        volatile bool *rB9,volatile bool *rB10,volatile bool *rB11,volatile bool *rB12,
        volatile bool *rB13,volatile bool *rB14,volatile bool *rB15,volatile bool *rB16,
        volatile float *rF1,volatile float *rF2,volatile float *rF3,volatile float *rF4,
        volatile float *rF5,volatile float *rF6,volatile float *rF7,volatile float *rF8,
        volatile float *rF9,
        volatile float *rC1,volatile float *rC2,volatile float *rC3,volatile float *rC4,
        volatile bool *wB1,volatile bool *wB2,volatile bool *wB3,volatile bool *wB4,
        volatile bool *wB5,volatile bool *wB6,volatile bool *wB7,volatile bool *wB8,
        volatile bool *wB9,volatile bool *wB10,volatile bool *wB11,volatile bool *wB12,
        volatile float *wF1,volatile float *wF2,volatile float *wF3,volatile float *wF4,
        volatile bool *wReset
    ) : rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},rB5{rB5},rB6{rB6},rB7{rB7},rB8{rB8},
    rB9{rB9},rB10{rB10},rB11{rB11},rB12{rB12},rB13{rB13},rB14{rB14},rB15{rB15},rB16{rB16},
    rF1{rF1},rF2{rF2},rF3{rF3},rF4{rF4},rF5{rF5},rF6{rF6},rF7{rF7},rF8{rF8},rF9{rF9},
    rC1{rC1},rC2{rC2},rC3{rC3},rC4{rC4},
    wB1{wB1},wB2{wB2},wB3{wB3},wB4{wB4},wB5{wB5},wB6{wB6},
    wB7{wB7},wB8{wB8},wB9{wB9},wB10{wB10},wB11{wB11},wB12{wB12},
    wF1{wF1},wF2{wF2},wF3{wF3},wF4{wF4},wReset{wReset},
     ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[36];
    memset(buffer, 0, 36 * sizeof(uint16_t));
    for(int i=0;i<13;i++)
        for(int j=0;j<4;j++)
            lin[i][j]=0;

}
OWEN_PLC160::~OWEN_PLC160() {
    delete[] buffer;
}

void OWEN_PLC160::Write() {
    if(wB1!=NULL||wB2!=NULL||wB3!=NULL||wB4!=NULL||wB5!=NULL||wB6!=NULL||wB7!=NULL||wB8!=NULL||wB9!=NULL||wB10!=NULL||wB11!=NULL||wB12!=NULL||wReset!=NULL) {
        uint16_t temp=
            (wB1==NULL)?0:(*wB1<<0)|
            (wB2==NULL)?0:(*wB2<<1)|
            (wB3==NULL)?0:(*wB3<<2)|
            (wB4==NULL)?0:(*wB4<<3)|
            (wB5==NULL)?0:(*wB5<<4)|
            (wB6==NULL)?0:(*wB6<<5)|
            (wB7==NULL)?0:(*wB7<<6)|
            (wB8==NULL)?0:(*wB8<<7)|
            (wB9==NULL)?0:(*wB9<<8)|
            (wB10==NULL)?0:(*wB10<<9)|
            (wB11==NULL)?0:(*wB11<<10)|
            (wB12==NULL)?0:(*wB12<<11)|
            (wReset==NULL)?0:(*wReset<<12);
        buffer[1]=temp; 
        Set();
        rc = modbus_write_registers(ctx, 1, 1, buffer+1);
        isError=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d %s\n",address, modbus_strerror(errno));
    }
    if(wF1!=NULL||wF2!=NULL||wF3!=NULL||wF4!=NULL) {
        if(wF1!=NULL) modbus_set_float_badc((lin[9][0]!=0||lin[9][1]!=0||lin[9][2]!=0||lin[9][3]!=0)?flin2(*wF1,lin[9][0],lin[9][1],lin[9][2],lin[9][3]):*wF1, buffer+20);
        if(wF2!=NULL) modbus_set_float_badc((lin[10][0]!=0||lin[10][1]!=0||lin[10][2]!=0||lin[10][3]!=0)?flin2(*wF2,lin[10][0],lin[10][1],lin[10][2],lin[10][3]):*wF2, buffer+22);
        if(wF3!=NULL) modbus_set_float_badc((lin[11][0]!=0||lin[11][1]!=0||lin[11][2]!=0||lin[11][3]!=0)?flin2(*wF3,lin[11][0],lin[11][1],lin[11][2],lin[11][3]):*wF3, buffer+24); 
        if(wF4!=NULL) modbus_set_float_badc((lin[12][0]!=0||lin[12][1]!=0||lin[12][2]!=0||lin[12][3]!=0)?flin2(*wF4,lin[12][0],lin[12][1],lin[12][2],lin[12][3]):*wF4, buffer+26); 
        Set();
        rc = modbus_write_registers(ctx, 20, 8, buffer+20);
        isError=(rc==-1);
        if (rc == -1) 
            fprintf(stderr, "#%d %s\n",address, modbus_strerror(errno));
    }
}

void OWEN_PLC160::Read() {
    Set();
    rc = modbus_read_input_registers(ctx, 0, 36, buffer);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "#%d Read() %s\n",address, modbus_strerror(errno)); 
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

        if(rF1!=NULL) *rF1=(lin[0][0]!=0||lin[0][1]!=0||lin[0][2]!=0||lin[0][3]!=0)?flin2(modbus_get_float_badc(buffer+2),lin[0][0],lin[0][1],lin[0][2],lin[0][3]):modbus_get_float_badc(buffer+2);
        if(rF2!=NULL) *rF2=(lin[1][0]!=0||lin[1][1]!=0||lin[1][2]!=0||lin[1][3]!=0)?flin2(modbus_get_float_badc(buffer+4),lin[1][0],lin[1][1],lin[1][2],lin[1][3]):modbus_get_float_badc(buffer+4);
        if(rF3!=NULL) *rF3=(lin[2][0]!=0||lin[2][1]!=0||lin[2][2]!=0||lin[2][3]!=0)?flin2(modbus_get_float_badc(buffer+6),lin[2][0],lin[2][1],lin[2][2],lin[2][3]):modbus_get_float_badc(buffer+6);
        if(rF4!=NULL) *rF4=(lin[3][0]!=0||lin[3][1]!=0||lin[3][2]!=0||lin[3][3]!=0)?flin2(modbus_get_float_badc(buffer+8),lin[3][0],lin[3][1],lin[3][2],lin[3][3]):modbus_get_float_badc(buffer+8);
        if(rF5!=NULL) *rF5=(lin[4][0]!=0||lin[4][1]!=0||lin[4][2]!=0||lin[4][3]!=0)?flin2(modbus_get_float_badc(buffer+10),lin[4][0],lin[4][1],lin[4][2],lin[4][3]):modbus_get_float_badc(buffer+10);
        if(rF6!=NULL) *rF6=(lin[5][0]!=0||lin[5][1]!=0||lin[5][2]!=0||lin[5][3]!=0)?flin2(modbus_get_float_badc(buffer+12),lin[5][0],lin[5][1],lin[5][2],lin[5][3]):modbus_get_float_badc(buffer+12);
        if(rF7!=NULL) *rF7=(lin[6][0]!=0||lin[6][1]!=0||lin[6][2]!=0||lin[6][3]!=0)?flin2(modbus_get_float_badc(buffer+14),lin[6][0],lin[6][1],lin[6][2],lin[6][3]):modbus_get_float_badc(buffer+14);
        if(rF8!=NULL) *rF8=(lin[7][0]!=0||lin[7][1]!=0||lin[7][2]!=0||lin[7][3]!=0)?flin2(modbus_get_float_badc(buffer+16),lin[7][0],lin[7][1],lin[7][2],lin[7][3]):modbus_get_float_badc(buffer+16);
        if(rF9!=NULL) *rF9=(lin[8][0]!=0||lin[8][1]!=0||lin[8][2]!=0||lin[8][3]!=0)?flin2(modbus_get_float_badc(buffer+18),lin[8][0],lin[8][1],lin[8][2],lin[8][3]):modbus_get_float_badc(buffer+18);

        if(rC1!=NULL) *rC1=modbus_get_float_badc(buffer+28);
        if(rC2!=NULL) *rC2=modbus_get_float_badc(buffer+30);
        if(rC3!=NULL) *rC3=modbus_get_float_badc(buffer+32);
        if(rC4!=NULL) *rC4=modbus_get_float_badc(buffer+34);
    }
}
void OWEN_PLC160::setFlin(int index,float x1,float y1,float x2,float y2) {
    lin[index][0]=x1;
    lin[index][1]=y1;
    lin[index][2]=x2;
    lin[index][3]=y2;
}
