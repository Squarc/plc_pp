#pragma once

#include <iostream>
#include <string>
#include <stdarg.h>
#include <time.h>   /* Needed for struct timespec */
#include <fstream>


class Logger
{
public:
    Logger() {}
    Logger(std::string path,std::string filename,bool timeDep=false);
    ~Logger();
    void SetFileName(std::string filename);
    void SetTimeDepFileName(std::string path,std::string filename);
    void WriteLog(const char *msg, ...);
    void WriteConLog(const char *msg, ...);
    void Message(std::string message);
private:
    time_t T;
    char s[80];
    bool timeDep=false;
    std::string path,filename;
};

