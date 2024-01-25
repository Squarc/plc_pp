#include "Delta_C2000.h"

Delta_C2000::Delta_C2000(modbus_t *ctx, int addr,volatile float *frq,volatile float *current,volatile bool *autostart,volatile bool *bStart,volatile bool *bStop,volatile bool *_state) :
    frq{frq},_autostart{autostart},current{current},bStart{bStart},bStop{bStop},_state{_state},ModbusModule(ctx,addr,false) {
    buffer = new uint16_t[1];
    memset(buffer, 0, 1 * sizeof(uint16_t));
    log = new Logger("/root","Modbus.log");
}

Delta_C2000::~Delta_C2000() {
    delete[] buffer;
    delete log;
}

void Delta_C2000::Write() {
    uint64_t tCurr=timeSinceEpochMillisec();
    Set();
    if(_autostart!=NULL)
        if(*_autostart) _start=*frq>0;
    if(state==1) {
        if(tCurr-tStart >3000) {
            if(bStart!=NULL) *bStart=false;
            state=2;
        }
    }
    if(state==2) {
        if(tCurr-tStart >8000) {
            if(bStart!=NULL) *bStart=false;
            state=0;
        }
    }

    if(frq!=NULL) {
        rc = modbus_write_register(ctx, 0x2001, (uint16_t)(*frq*100));
        if(*frq==0&& _state!=NULL) *_state=false;
        if (rc == -1) {
            if(wE1!=errno) log->WriteConLog("#%d Delta_C2000::Write(uint16_t frq) %s\n", address, modbus_strerror(errno));
            errorCount++;
            if(errorCount>100) errorCount=100;
            if(_autostart!=NULL&& *_autostart &&state==0&&isError) {
                state=1;
                tStart=tCurr;
                if(bStart!=NULL) *bStart=true;
            }
        }
        else {
            if(*frq>0&& _state!=NULL) *_state=true;
            errorCount=0;
            if(wE1!=errno) log->WriteConLog("#%d Delta_C2000::Write(uint16_t frq) OK\n", address);
            state=0;
            if(bStart!=NULL) *bStart=false;

        }
        wE1=errno;
        isError=(errorCount>3);
        isChanged=(oldIsError!=isError);
        oldIsError=isError;
    }
    rc = modbus_write_register(ctx, 0x2000, _start?4:2);
    if (rc == -1) {
        if(wE2!=errno) log->WriteConLog("#%d Delta_C2000::Start() %s\n", address, modbus_strerror(errno));
        errorCount++;
        if(errorCount>100) errorCount=100;
    }
    else {
        errorCount=0;
        if(wE2!=errno) log->WriteConLog("#%d Delta_C2000::Start() OK\n", address);
    }
    wE2=errno;
    isError=(errorCount>3);
    isChanged=(oldIsError!=isError);
    oldIsError=isError;

}

void Delta_C2000::Start() {
    _start=true;
}
void Delta_C2000::Stop() {
    _start=false;
}

void Delta_C2000::Read() {
    Set();
    rc = modbus_read_registers(ctx, 0x2104,1, buffer);
    if (rc == -1) {
        if(rE1!=errno) log->WriteConLog("#%d Delta_C2000::Start() %s\n", address, modbus_strerror(errno));
        errorCount++;
        if(errorCount>100) errorCount=100;
    }
    else {
        if(rE1!=errno) log->WriteConLog("#%d Delta_C2000::Start() OK\n", address);
        errorCount=0;
        if(current!=NULL) *current=(float)(buffer[0])/100.0f;
    }
    rE1=errno;
    isError=(errorCount>3);
    isChanged=(oldIsError!=isError);
    oldIsError=isError;
}

