#include "MqttDevice.h"

#define mqtt_port 1883
MqttDevice::MqttDevice(string Id,string mqtt_host,string logPath,string startTag) : Id{Id},startTag{startTag},mqtt_host{mqtt_host}, mosquittopp((Id+to_string(rand())).c_str()) {
    _exit=false;
    log=new Logger(logPath,"MqttDevice.log");
    int rc=connect(mqtt_host.c_str(),mqtt_port,65535);
    printf("MqttDevice connect %d\n",rc);
    _threadMosquitto = thread(&MqttDevice::mosq_loop,this);
    log->WriteLog("Start MqttDevice Id=%s",Id.c_str());
}
MqttDevice::~MqttDevice() {
    _exit=true;
    _threadMosquitto.join();
    log->WriteLog("Stop MqttDevice Id=%s",Id.c_str());
    delete log;
    printf("MqttDevice delete\n");
}

void MqttDevice::addSubscribed(string topic, volatile bool* value) {
    lwBool.push_back({topic,false,value,0});
    if(subscribe(0,topic.c_str(),0)==MOSQ_ERR_SUCCESS) printf("[Mosquitto] Subscribing to topic %s\n",topic.c_str());
}
void MqttDevice::addSubscribed(string topic, volatile float* value) {
    lwFloat.push_back({topic,0.0f,value,1});
    if(subscribe(0,topic.c_str(),0)==MOSQ_ERR_SUCCESS) printf("[Mosquitto] Subscribing to topic %s\n",topic.c_str());
}
void MqttDevice::addSubscribed(string topic, volatile uint16_t* value) {
    lwUInt16.push_back({topic,value});
    if(subscribe(0,topic.c_str(),0)==MOSQ_ERR_SUCCESS) printf("[Mosquitto] Subscribing to topic %s\n",topic.c_str());
}
void MqttDevice::add(string topic,volatile bool* value) {
    lrBool.push_back({topic,false,value,0});
}
void MqttDevice::add(string topic,volatile uint16_t* value) {
    lrUInt16.push_back({topic,0,value,0});
}
void MqttDevice::add(string topic,volatile float* value, int precision) {
    lrFloat.push_back({topic,0.0f,value,precision});
}
void MqttDevice::add(string topic,volatile double* value, int precision) {
    lrDouble.push_back({topic,0.0,value,precision});
}
void MqttDevice::add(ValveA* valve) {
    add(startTag+"/"+valve->name+"/SQL",valve->b_t1);
    add(startTag+"/"+valve->name+"/SQH",valve->b_t2);
    add(startTag+"/"+valve->name+"/out",valve->b_out);
    addSubscribed(startTag+"/"+valve->name+"/auto",valve->b_mode);
    addSubscribed(startTag+"/"+valve->name+"/man",valve->b_control);
}
void MqttDevice::add(ValveM* valve) {
    add(startTag+"/"+valve->name+"/SQL",valve->b_t1);
    add(startTag+"/"+valve->name+"/SQH",valve->b_t2);
}
void MqttDevice::add(ValveD* valve) {
    add(startTag+"/"+valve->name+"/SQL",valve->b_t1);
    add(startTag+"/"+valve->name+"/SQH",valve->b_t2);
    add(startTag+"/"+valve->name+"/out",valve->b_out);
    addSubscribed(startTag+"/"+valve->name+"/auto",valve->b_mode);
    addSubscribed(startTag+"/"+valve->name+"/man",valve->b_control);
}
void MqttDevice::add(Heating* valve) {
    addSubscribed(startTag+"/"+valve->name+"/start",valve->_start);
    addSubscribed(startTag+"/"+valve->name+"/tempMin",valve->_tempMin);
    addSubscribed(startTag+"/"+valve->name+"/tempMax",valve->_tempMax);
}
void MqttDevice::add(Cooling* valve) {
    addSubscribed(startTag+"/"+valve->name+"/start",valve->_start);
    addSubscribed(startTag+"/"+valve->name+"/tempMin",valve->_tempMin);
    addSubscribed(startTag+"/"+valve->name+"/tempMax",valve->_tempMax);
}
void MqttDevice::add(Pump* valve) {
    addSubscribed(startTag+"/"+valve->name+"/auto",valve->b_mode);
    addSubscribed(startTag+"/"+valve->name+"/man",valve->b_control);
    add(startTag+"/"+valve->name+"/state",valve->b_out);
}
void MqttDevice::add(Loading* valve) {
    addSubscribed(startTag+"/"+valve->name+"/start",valve->b_start);
    addSubscribed(startTag+"/"+valve->name+"/load",valve->f_Load);
    add(startTag+"/"+valve->name+"/loaded",valve->f_Loaded);
}
void MqttDevice::add(Loading1S* valve) {
    addSubscribed(startTag+"/"+valve->name+"/start",valve->b_start);
    addSubscribed(startTag+"/"+valve->name+"/load",valve->f_Load);
    addSubscribed(startTag+"/"+valve->name+"/set1",valve->set1);
    add(startTag+"/"+valve->name+"/loaded",valve->f_Loaded);
}
void MqttDevice::add(Purge* valve) {
    addSubscribed(startTag+"/"+valve->name+"/start",valve->b_start);
    addSubscribed(startTag+"/"+valve->name+"/time",valve->f_time);
    add(startTag+"/"+valve->name+"/passed",valve->f_passed);
}


void MqttDevice::on_connect(int rc) {
    int err=0;    
    log->WriteLog("on_connect() rc=%d",rc);
    printf("[Mosquitto] Connect. rc=%d\n",rc);
    if(rc==0) {
        for(auto& v:lwBool) {
            err=subscribe(0,v.topic.c_str(),0);
            if(err==MOSQ_ERR_SUCCESS) printf("[Mosquitto] Subscribing to topic %s\n",v.topic.c_str());
            
            nsleep(10);
        }
        for(auto& v:lwFloat) {
            err=subscribe(0,v.topic.c_str(),0);
            if(err==MOSQ_ERR_SUCCESS) printf("[Mosquitto] Subscribing to topic %s\n",v.topic.c_str());
            
            nsleep(10);
        }
    } 
    else 
        printf("[Mosquitto] Connection failed. Aborting subscribing.\n");
}

void MqttDevice::on_message(const struct mosquitto_message *message) {
    string tag=message->topic;
    string value=string((const char*)message->payload,message->payloadlen);
    setTag(tag,value);
}
void MqttDevice::mosq_loop() {
    int rc;
    lib_init();
    printf("[Mosquitto] Start loop...\n");
    bool rcReconnect=false;
    while(!_exit) {
        uint64_t now = timeSinceEpochMillisec();  
        rc=loop(); 
        if(oldRc!=rc) {log->WriteLog("mosq_loop() loop() rc=%d");oldRc=rc;}
        if(rc) {
            printf("[Mosquitto] Disconnected. Trying to reconnect...\n");
            nsleep(500);
            if(rcReconnect) {
                rc=connect(mqtt_host.c_str(),mqtt_port,65535);
                {log->WriteLog("mosq_loop() connect() rc=%d");oldRc=rc;}
            } else {
                rc=reconnect();
                {log->WriteLog("mosq_loop() reconnect() rc=%d");oldRc=rc;}
                if(rc) rcReconnect=true;
            }
            nsleep(500);
            continue;
        }
        while(messages.size()>0) {
            rc=publish(NULL,get<0>(messages.front()).c_str(),strlen(get<1>(messages.front()).c_str()),(const uint8_t*)get<1>(messages.front()).c_str(),0,true);
            {log->WriteLog("mosq_loop() publish() rc=%d");oldRc=rc;}
            if(rc) {
                printf("[Mosquitto] Error send message\n");
                break;
            }
            else
                messages.pop_front();
        }
        if(now-tBool>300) {
            tBool=now;
            for(auto &v:lrBool) {
                if(v.current==NULL) continue;
                if(v.old!=*v.current || now-v.tFlag>3000) {
                    v.tFlag=now;
                    v.old=*v.current;
                    message(v.topic,*v.current);
                }
            }
            for(auto &v:lwBool) {
                if(v.old!=*v.current || now-v.tFlag>3000) {
                    v.tFlag=now;
                    v.old=*v.current;
                    message(v.topic,*v.current);
                }
            }
        }
        if(now-tFloat>500) {
            tFloat=now;
            for(auto &v:lrFloat) {
                float r=round(*v.current*pow(10,v.precision))/pow(10,v.precision);
                if(v.old!=r || now-v.tFlag>5000) {
                    v.tFlag=now;
                    v.old=r;
                    message(v.topic,r);
                }
            }
            for(auto &v:lrDouble) {
                double r=round(*v.current*pow(10,v.precision))/pow(10,v.precision);
                if(v.old!=r || now-v.tFlag>5000) {
                    v.tFlag=now;
                    v.old=r;
                    message(v.topic,r);
                }
            }
            for(auto &v:lwFloat) {
                //cout<<v.topic<<" = "<<*(v.current)<<endl;
                float r=round(*v.current*pow(10,v.precision))/pow(10,v.precision);
                if(v.old!=r || now-v.tFlag>5000) {
                    v.tFlag=now;
                    v.old=r;
                    message(v.topic,r);
                }
            }
            for(auto &v:lrUInt16) {
                if(v.old!=*v.current || now-v.tFlag>5000) {
                    v.tFlag=now;
                    v.old=*v.current;
                    message(v.topic,*v.current);
                }
            }
        }
        //nsleep(100);
        //printf(".");fflush(stdout);
    }
    lib_cleanup();
    printf("[Mosquitto] Exit from mosquitto loop.\n");
}

void MqttDevice::message(string name, volatile float value) {
    messages.push_back(make_tuple(name,to_string(value)));
}
void MqttDevice::message(string name, volatile double value) {
    messages.push_back(make_tuple(name,to_string(value)));
}
void MqttDevice::message(string name, volatile uint16_t value) {
    messages.push_back(make_tuple(name,to_string(value)));
}
void MqttDevice::message(string name, volatile bool value) {
    messages.push_back(make_tuple(name,(value?"true":"false")));
}
void MqttDevice::message(string name, string value) {
    messages.push_back(make_tuple(name,value));
}

void MqttDevice::setTag(string topic,string value) {
    try {
        for(auto& v:lwBool)
            if(v.topic==topic) {
                *(v.current)=(value=="true");
                v.old=*(v.current);
                return;
            }
        for(auto& v:lwFloat)
            if(v.topic==topic) {
                *(v.current)=(float)atof(value.c_str());
                v.old=*(v.current);
                return;
            }
        for(auto& v:lwUInt16)
            if(v.first==topic) {
                *(v.second)=(uint16_t)atoi(value.c_str());
                
                return;
            }
    }
    catch(const std::exception&) { }
}