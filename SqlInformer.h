#pragma once

#include <stdio.h>
#include <mysql.h>
#include <pigment/Logger.h>
#include <pigment/util.h>
#include <thread>
#include <list>


class SqlInformer
{
public:
    SqlInformer(int asutpID,char* serverIP,char* username,char* password,char* database);
    ~SqlInformer();
    void startOperation(int operation,int recipe);
    void stopOperation(int operation,int recipe);
    void startLimitter(float minValue,float maxValue);
    void stopLimitter(float minValue,float maxValue);
    void startProcess(char* text,float minVal,float maxVal);
    void startProcess(char* text,float minVal,float maxVal,float value);
    void stopProcess(char* text);
private:
    void sendInfo();
    int asutpID;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
  	char szsqlcmd[128];

    char *serverip,*username,*password,*database;
    Logger log;
    list<string> commands;
    thread _thread;
    bool _stop=false;
};
