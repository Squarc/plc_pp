#include "ModbusModule.h"



ModbusModule::ModbusModule(modbus_t *ctx, int addr, bool setNullable) :
    ctx{ctx},address{addr},setNullable{setNullable} { }

ModbusModule::~ModbusModule() { }

void ModbusModule::Set() {
    modbus_flush(ctx);
    modbus_set_slave(ctx,address);
    usleep(5000);
}

