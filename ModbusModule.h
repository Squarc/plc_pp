#pragma once

#include <stdio.h>
#include <unistd.h>

#include <time.h>
#include <pigment/util.h>
#include <modbus.h>
#include <string.h>

class ModbusModule
{
public:

    ModbusModule(modbus_t *ctx, int addr, bool setNullable=false);
    virtual ~ModbusModule();
    virtual void Read() {};
    virtual void Write() {};
    bool isError=true,isChanged=true;
    int error=0;
protected:
    bool oldIsError=false;
    int rc,olderror,errorCount=0;

protected:
    bool setNullable=false;
    void Set();
    modbus_t *ctx;
    int address;
};

