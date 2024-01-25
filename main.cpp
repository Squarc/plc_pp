#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <map>
#include <string>
#include <plc_pp/ModbusLine.h>
#include <plc_pp/Influx.h>
#include <plc_pp/MqttDevice.h>
#include <plc_pp/Device.h>

using namespace std;

bool stop;
volatile float T_D2705,L_D2705,W_D2705,W_D2701; // данные с датчиков

volatile float TV_D2705_out,TV_D2705_in,TV_D2705_man; // регулирующий клапан
volatile bool TV_D2705_auto;

volatile bool LV_G2705_SQL,LV_G2705_SQH,LV_G2705_out,LV_G2705_man,LV_G2705_auto; // отсечной клапан
volatile bool WV_D2705_SQL,WV_D2705_SQH,WV_D2705_out,WV_D2705_man,WV_D2705_auto;
volatile bool NV_D2705_SQL,NV_D2705_SQH,NV_D2705_out,NV_D2705_man,NV_D2705_auto;
volatile bool NV_D2701_SQL,NV_D2701_SQH,NV_D2701_out,NV_D2701_man,NV_D2701_auto;
volatile bool LV_G2066_SQL,LV_G2066_SQH,LV_G2066_out,LV_G2066_man,LV_G2066_auto;
volatile bool V4_D2701_SQL,V4_D2701_SQH,V4_D2701_out,V4_D2701_man,V4_D2701_auto;

volatile bool MV1_SQL,MV1_SQH; // ручной клапан
volatile bool MV2_SQL,MV2_SQH;
volatile bool MV3_SQL,MV3_SQH;
volatile bool MV4_SQL,MV4_SQH;
volatile bool MV5_SQL,MV5_SQH;
volatile bool MV6_SQL,MV6_SQH;
volatile bool MV7_SQL,MV7_SQH;
volatile bool MV8_SQL,MV8_SQH;
volatile bool MV9_SQL,MV9_SQH;
volatile bool MV10_SQL,MV10_SQH;
volatile bool MV11_SQL,MV11_SQH;
volatile bool MV12_SQL,MV12_SQH;
volatile bool MV13_SQL,MV13_SQH;
volatile bool MV14_SQL,MV14_SQH;

void handle_signal(int i) {
    printf("[MAIN] Terminating\n");
    stop=true;
}
void handle_no(int i) { 
    printf("[MAIN] Handle pipe signal...\n");  
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal); 
    signal(SIGPIPE, handle_no);     
    stop = false;
    printf("[MAIN] My pid is %i\n", getpid()); 
    ModbusLine line1(modbus_new_rtu("/dev/ttyS2", 115200, 'N', 8, 1));
    line1.addMDS_AI_8UI(1,&T_D2705,&L_D2705,&TV_D2705_in);
    line1.addMDS_DIO_16BD(2,&LV_G2705_out,&WV_D2705_out,&NV_D2705_out,&NV_D2701_out,&LV_G2066_out,&V4_D2701_out);
    line1.addMDS_DIO_16BD(3,&LV_G2705_SQH,&LV_G2705_SQL,&WV_D2705_SQH,&WV_D2705_SQL,&NV_D2705_SQH,&NV_D2705_SQL,&NV_D2701_SQH,&NV_D2701_SQL,&LV_G2066_SQH,&LV_G2066_SQL,&V4_D2701_SQH,&V4_D2701_SQL);
    line1.addMDS_DIO_16BD(4,&MV1_SQH,&MV1_SQL,&MV2_SQH,&MV2_SQL,&MV3_SQH,&MV3_SQL,&MV4_SQH,&MV4_SQL,&MV5_SQH,&MV5_SQL,&MV6_SQH,&MV6_SQL,&MV7_SQH,&MV7_SQL,&MV8_SQH,&MV8_SQL);
    line1.addMDS_DIO_16BD(5,&MV9_SQH,&MV9_SQL,&MV10_SQH,&MV10_SQL,&MV11_SQH,&MV11_SQL,&MV12_SQH,&MV12_SQL,&MV13_SQH,&MV13_SQL,&MV14_SQH,&MV14_SQL);
    line1.addMDS_AO_2UI(6,&TV_D2705_out);
    ModbusLine line2(modbus_new_rtu("/dev/ttyS3", 115200, 'N', 8, 1));
    line2.addTenzoM_TV006c(1,&W_D2705,1);
    ModbusLine line3(modbus_new_rtu("/dev/ttyS4", 115200, 'N', 8, 1));
    line3.addTenzoM_TV006c(1,&W_D2701,1);

    MqttDevice mqtt("line","localhost","/root");
    mqtt.add("device/T_D2705",&T_D2705);
    mqtt.add("device/L_D2705",&L_D2705);

    Influx inf("CEX","line",10000U);
    inf.addNotNull(&T_D2705);
    inf.add("T_D2705",&T_D2705);
    inf.add("L_D2705",&L_D2705);
    inf.add("W_D2705",&W_D2705);
    inf.add("W_D2701",&W_D2701);

    Device dev(&mqtt);
    dev.addValveM("MV1",&MV1_SQL,&MV1_SQH);
    dev.addValveM("MV2",&MV2_SQL,&MV2_SQH);
    dev.addValveM("MV3",&MV3_SQL,&MV3_SQH);
    dev.addValveM("MV4",&MV4_SQL,&MV4_SQH);
    dev.addValveM("MV5",&MV5_SQL,&MV5_SQH);
    dev.addValveM("MV6",&MV6_SQL,&MV6_SQH);
    dev.addValveM("MV7",&MV7_SQL,&MV7_SQH);
    dev.addValveM("MV8",&MV8_SQL,&MV8_SQH);
    dev.addValveM("MV9",&MV9_SQL,&MV9_SQH);
    dev.addValveM("MV10",&MV10_SQL,&MV10_SQH);
    dev.addValveM("MV11",&MV11_SQL,&MV11_SQH);
    dev.addValveM("MV12",&MV12_SQL,&MV12_SQH);
    dev.addValveM("MV13",&MV13_SQL,&MV13_SQH);
    dev.addValveM("MV14",&MV14_SQL,&MV14_SQH);
    dev.addValveA("TV_D2705",NULL,NULL,&TV_D2705_man,&TV_D2705_auto,&TV_D2705_out);
    dev.addValveD("LV_G2705",&LV_G2705_SQL,&LV_G2705_SQH,&LV_G2705_man,&LV_G2705_auto,&LV_G2705_out);
    dev.addValveD("WV_D2705",&WV_D2705_SQL,&WV_D2705_SQH,&WV_D2705_man,&WV_D2705_auto,&WV_D2705_out);
    dev.addValveD("NV_D2705",&NV_D2705_SQL,&NV_D2705_SQH,&NV_D2705_man,&NV_D2705_auto,&NV_D2705_out);
    dev.addValveD("NV_D2701",&NV_D2701_SQL,&NV_D2701_SQH,&NV_D2701_man,&NV_D2701_auto,&NV_D2701_out);
    dev.addValveD("LV_G2066",&LV_G2066_SQL,&LV_G2066_SQH,&LV_G2066_man,&LV_G2066_auto,&LV_G2066_out);
    dev.addValveD("V4_D2701",&V4_D2701_SQL,&V4_D2701_SQH,&V4_D2701_man,&V4_D2701_auto,&V4_D2701_out);

    long t=timeSinceEpochMillisec();

    while(!stop){
        uint64_t cT=timeSinceEpochMillisec();
        if(cT-t>1000) {
            time_t T = time(NULL);
            struct tm *u;
            char s[80] = { 0 };
            time(&T);
            u = localtime(&T);
            strftime(s, 80, "%d.%m.%Y %H:%M:%S ",u);
            string st=s;
            mqtt.message("modules/line",st);
            t+=1000;
        }

        nsleep(1000);
    }
    printf("Exit\n");
    return 0;
}


