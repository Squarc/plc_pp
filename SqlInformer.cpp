//#define DEBUG

#include "SqlInformer.h"

SqlInformer::SqlInformer(int asutpID,char* serverIP,char* username,char* password,char* database):
    asutpID{asutpID},serverip{serverIP},username{username},password{password},database{database}
{
    log.SetFileName("/root/SqlInformer.log");
   	conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, serverip,username, password,	database, 0, NULL, 0)) {
        log.WriteLog( mysql_error(conn));
    }
    _thread = thread(&SqlInformer::sendInfo,this);
}

SqlInformer::~SqlInformer() {
    _stop=true;
    mysql_close(conn);
    if(_thread.joinable()) _thread.join();
    log.WriteLog("SqlInformer: Deleting");
}

void SqlInformer::startOperation(int operation,int recipe) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,status,recipe) VALUE (%d,1,%d,%d)",asutpID,operation,recipe);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif

}
void SqlInformer::stopOperation(int operation,int recipe) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,status,recipe) VALUE (%d,2,%d,%d)",asutpID,operation,recipe);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}

void SqlInformer::startLimitter(float minValue,float maxValue) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,status,recipe) VALUE (%d,3,%d,%d)",asutpID,(int)(minValue*10),(int)(maxValue*10));
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}

void SqlInformer::stopLimitter(float minValue,float maxValue) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event) VALUE (%d,4)",asutpID);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}

void SqlInformer::startProcess(char* text,float minVal,float maxVal) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,status,recipe,text) VALUE (%d,5,%d,%d,'%s')",asutpID,(int)(minVal*10),(int)(maxVal*10),text);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}
void SqlInformer::startProcess(char* text,float minVal,float maxVal,float value) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,status,recipe,text,value) VALUE (%d,5,%d,%d,'%s',%f)",asutpID,(int)(minVal*10),(int)(maxVal*10),text,value);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}

void SqlInformer::stopProcess(char* text) {
    snprintf(szsqlcmd,sizeof(szsqlcmd),"INSERT INTO log (asutp,event,text) VALUE (%d,6,'%s')",asutpID,text);
#ifdef DEBUG
    printf("%s\n",szsqlcmd);
#else
    commands.push_back(szsqlcmd);
#endif
}

void SqlInformer::sendInfo() {
    while(!_stop) {
        if(commands.size()>0) {
            if (mysql_query(conn, commands.front().c_str())) {
                log.Message(mysql_error(conn));
                nsleep(1000); log.Message("Пробуем переподключиться");
                if (!mysql_real_connect(conn, serverip,username, password,	database, 0, NULL, 0))
                    log.Message(mysql_error(conn));
                else if (mysql_query(conn, commands.front().c_str())) 
                    log.Message(mysql_error(conn));
                else commands.pop_front();
            }
            else {
                commands.pop_front();
            }
        }
        nsleep(1000);
    }
}



