#pragma once

#include <iostream>
#include <exception>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string>
#include <string.h>
#include <pigment/util.h>
#include <mosquitto.h>
#include <mosquittopp.h>
#include <list>
#include <math.h>
#include <chrono>
#include "Valve.h"
#include "Heating.h"
#include "Cooling.h"
#include "Pump.h"
#include "Loading.h"
#include "Purge.h"
#include "Loading1S.h"
#include "Logger.h"

using namespace std;
using namespace mosquittopp;

template<typename T>
struct Value {
    Value(string topic,T old, T* current,int precision):
        topic{topic},old{old},current{current},precision{precision} { }
    ~Value() { }
    string topic;
    T old;
    T* current;
    uint64_t tFlag=timeSinceEpochMillisec();
    int precision=2;
};

class MqttDevice:public mosquittopp::mosquittopp
{
public:
    
    MqttDevice(string Id,string mqtt_host,string logPath,string startTag="device");
    ~MqttDevice();
    // void setTag(string name,string tag,bool value);
    // void setTag(string name,string tag,float value);
    void setTag(string topic,string value);
    void message(string name, volatile double value);
    void message(string name, volatile float value);
    void message(string name, volatile uint16_t value);
    void message(string name, volatile bool value); 
    void message(string name, string value); 
    list< tuple<string,string> > messages;

    void on_connect(int rc);
    void on_message(const struct mosquitto_message* message);
    void on_subscribe(int mid,int qos_count,const int* granted_qos);
    void sendMessage(string topic, string& message);
    void sendMessage(string& topic,char* message, int msgLength);
    void addSubscribed(string topic, volatile bool* value);
    void addSubscribed(string topic, volatile float* value);
    void addSubscribed(string topic, volatile uint16_t* value);
    void add(string topic,volatile bool* value);
    void add(string topic,volatile uint16_t* value);
    void add(string topic,volatile float* value,int precision=1);
    void add(string topic,volatile double* value,int precision=1);
    void add(ValveA* value);
    void add(ValveD* value);
    void add(ValveM* value);
    void add(Heating* value);
    void add(Cooling* value);
    void add(Pump* value);
    void add(Loading* value);
    void add(Loading1S* value);
    void add(Purge* value);
protected:
    uint64_t tBool=0,tFloat=0,tDouble=0;

    bool _exit;

private:
    string mqtt_host;
    list<Value<volatile bool> > lwBool;
    list<Value<volatile float> > lwFloat;
    list<pair<string,volatile uint16_t*> > lwUInt16;
    list<Value<volatile bool> > lrBool;
    list<Value<volatile uint16_t> > lrUInt16;
    list<Value<volatile float> > lrFloat;
    list<Value<volatile double> > lrDouble;
    struct mosquitto *mosq;
    pthread_mutex_t mosq_mtx;
    string startTag,Id,logPath;
    void mosq_loop();
    thread _threadMosquitto;
    Logger *log;    int oldRc=-1;

};

