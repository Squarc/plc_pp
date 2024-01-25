#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>

#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <pigment/util.h>
#include <list>
//#include <iostream>

using namespace std;

class Influx
{
public:
    Influx(string DB,string title,uint msecs=1000);
    ~Influx();
    void add(string name,volatile double* value);
    void add(string name,volatile float* value);
    void add(string name,volatile bool* value);
    void addNotNull(volatile float* value);

private:
    void Thread();
    list<volatile float*> lfNotNull;
    list<pair<string,volatile double*> > ldValue;
    list<pair<string,volatile float*> > lfValue;
    list<pair<string,volatile bool*> > lbValue;
    string DB,title;
    thread _T;
    bool _exit;
    uint msecs;
};


