#include "OWEN-PLC110.60.h"

OWEN_PLC110_60::OWEN_PLC110_60(modbus_t *ctx, int addr,
    volatile bool *rB1, volatile bool *rB2, volatile bool *rB3, volatile bool *rB4,
    volatile bool *rB5, volatile bool *rB6, volatile bool *rB7, volatile bool *rB8,
    volatile bool *rB9, volatile bool *rB10, volatile bool *rB11, volatile bool *rB12,
    volatile bool *rB13, volatile bool *rB14, volatile bool *rB15, volatile bool *rB16,
    volatile bool *rB17, volatile bool *rB18, volatile bool *rB19, volatile bool *rB20,
    volatile bool *rB21, volatile bool *rB22, volatile bool *rB23, volatile bool *rB24,
    volatile bool *rB25, volatile bool *rB26, volatile bool *rB27, volatile bool *rB28,
    volatile bool *rB29, volatile bool *rB30, volatile bool *rB31, volatile bool *rB32,
    volatile bool *rB33, volatile bool *rB34, volatile bool *rB35, volatile bool *rB36,
    volatile bool *wB1, volatile bool *wB2, volatile bool *wB3, volatile bool *wB4,
    volatile bool *wB5, volatile bool *wB6, volatile bool *wB7, volatile bool *wB8,
    volatile bool *wB9, volatile bool *wB10, volatile bool *wB11, volatile bool *wB12,
    volatile bool *wB13, volatile bool *wB14, volatile bool *wB15, volatile bool *wB16,
    volatile bool *wB17, volatile bool *wB18, volatile bool *wB19, volatile bool *wB20,
    volatile bool *wB21, volatile bool *wB22, volatile bool *wB23, volatile bool *wB24)
    : rB1{rB1},rB2{rB2},rB3{rB3},rB4{rB4},rB5{rB5},rB6{rB6},rB7{rB7},rB8{rB8},
    rB9{rB9},rB10{rB10},rB11{rB11},rB12{rB12},rB13{rB13},rB14{rB14},rB15{rB15},rB16{rB16},
    rB17{rB17},rB18{rB18},rB19{rB19},rB20{rB20},rB21{rB21},rB22{rB22},rB23{rB23},rB24{rB24},
    rB25{rB25},rB26{rB26},rB27{rB27},rB28{rB28},rB29{rB29},rB30{rB30},rB31{rB31},rB32{rB32},
    rB33{rB33},rB34{rB34},rB35{rB35},rB36{rB36},
    wB1{wB1},wB2{wB2},wB3{wB3},wB4{wB4},wB5{wB5},wB6{wB6},wB7{wB7},wB8{wB8},wB9{wB9},
    wB10{wB10},wB11{wB11},wB12{wB12},wB13{wB13},wB14{wB14},wB15{wB15},wB16{wB16},wB17{wB17},
    wB18{wB18},wB19{wB19},wB20{wB20},wB21{wB21},wB22{wB22},wB23{wB23},wB24{wB24},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[5];
    memset(buffer, 0, 5 * sizeof(uint16_t));
}
OWEN_PLC110_60::~OWEN_PLC110_60() {
    delete[] buffer;
}

void OWEN_PLC110_60::Write() {
    uint16_t temp;
    temp=(wB1==NULL)?0:(((*wB1^r1)>>0)&1)|
        (wB2==NULL)?0:(((*wB2^r2)>>1)&1)|
        (wB3==NULL)?0:(((*wB3^r3)>>2)&1)|
        (wB4==NULL)?0:(((*wB4^r4)>>3)&1)|
        (wB5==NULL)?0:(((*wB5^r5)>>4)&1)|
        (wB6==NULL)?0:(((*wB6^r6)>>5)&1)|
        (wB7==NULL)?0:(((*wB7^r7)>>6)&1)|
        (wB8==NULL)?0:(((*wB8^r8)>>7)&1)|
        (wB9==NULL)?0:(((*wB9^r9)>>8)&1)|
        (wB10==NULL)?0:(((*wB10^r10)>>9)&1)|
        (wB11==NULL)?0:(((*wB11^r11)>>10)&1)|
        (wB12==NULL)?0:(((*wB12^r12)>>11)&1)|
        (wB13==NULL)?0:(((*wB13^r13)>>12)&1)|
        (wB14==NULL)?0:(((*wB14^r14)>>13)&1)|
        (wB15==NULL)?0:(((*wB15^r15)>>14)&1)|
        (wB16==NULL)?0:(((*wB16^r16)>>15)&1);
    buffer[3]=temp;
    temp=(wB17==NULL)?0:(((*wB17^r17)>>0)&1)|
        (wB18==NULL)?0:(((*wB18^r18)>>1)&1)|
        (wB19==NULL)?0:(((*wB19^r19)>>2)&1)|
        (wB20==NULL)?0:(((*wB20^r20)>>3)&1)|
        (wB21==NULL)?0:(((*wB21^r21)>>4)&1)|
        (wB22==NULL)?0:(((*wB22^r22)>>5)&1)|
        (wB23==NULL)?0:(((*wB23^r23)>>6)&1)|
        (wB24==NULL)?0:(((*wB24^r24)>>7)&1);
    buffer[4]=temp; 
    Set();
    rc = modbus_write_registers(ctx, 3, 2, buffer+3);
    isError=(rc==-1);
    if (rc == -1) 
        fprintf(stderr, "%s\n", modbus_strerror(errno));
}

void OWEN_PLC110_60::Read() {
    Set();
    rc = modbus_read_input_registers(ctx, 0, 5, buffer);
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
        if(rB17!=NULL) *rB17=(buffer[1]>>0)&1;
        if(rB18!=NULL) *rB18=(buffer[1]>>1)&1;
        if(rB19!=NULL) *rB19=(buffer[1]>>2)&1;
        if(rB20!=NULL) *rB20=(buffer[1]>>3)&1;
        if(rB21!=NULL) *rB21=(buffer[1]>>4)&1;
        if(rB22!=NULL) *rB22=(buffer[1]>>5)&1;
        if(rB23!=NULL) *rB23=(buffer[1]>>6)&1;
        if(rB24!=NULL) *rB24=(buffer[1]>>7)&1;
        if(rB25!=NULL) *rB25=(buffer[1]>>8)&1;
        if(rB26!=NULL) *rB26=(buffer[1]>>9)&1;
        if(rB27!=NULL) *rB27=(buffer[1]>>10)&1;
        if(rB28!=NULL) *rB28=(buffer[1]>>11)&1;
        if(rB29!=NULL) *rB29=(buffer[1]>>12)&1;
        if(rB30!=NULL) *rB30=(buffer[1]>>13)&1;
        if(rB31!=NULL) *rB31=(buffer[1]>>14)&1;
        if(rB32!=NULL) *rB32=(buffer[1]>>15)&1;
        if(rB33!=NULL) *rB33=(buffer[2]>>0)&1;
        if(rB34!=NULL) *rB34=(buffer[2]>>1)&1;
        if(rB35!=NULL) *rB35=(buffer[2]>>2)&1;
        if(rB36!=NULL) *rB36=(buffer[2]>>3)&1;
    }
}
void OWEN_PLC110_60::setReverse(int index) {
    if(index==0) r1=true;
    if(index==1) r2=true;
    if(index==2) r3=true;
    if(index==3) r4=true;
    if(index==4) r5=true;
    if(index==5) r6=true;
    if(index==6) r7=true;
    if(index==7) r8=true;
    if(index==8) r9=true;
    if(index==9) r10=true;
    if(index==10) r11=true;
    if(index==11) r12=true;
    if(index==12) r13=true;
    if(index==13) r14=true;
    if(index==14) r15=true;
    if(index==15) r16=true;
    if(index==16) r17=true;
    if(index==17) r18=true;
    if(index==18) r19=true;
    if(index==19) r20=true;
    if(index==20) r21=true;
    if(index==21) r22=true;
    if(index==22) r23=true;
    if(index==23) r24=true;
}
