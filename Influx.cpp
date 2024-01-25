#include "Influx.h"

Influx::Influx(string DB,string title,uint msecs):
    DB{DB},title{title},msecs{msecs} {
    _exit=false;
    _T=thread(&Influx::Thread,this);
    printf("Influx create\n");
}

Influx::~Influx() {
    _exit=true;
    _T.join();
    printf("Influx delete\n");

}

void Influx::Thread() {
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Error create UDP socket");
		return ;
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(8089);

	if (inet_aton("192.168.150.133" , &si_other.sin_addr) == 0)
	{
		printf("inet_aton() failed");
		return ;
	}
    //cout<<"In while..."<<endl;
    while( !_exit ){
        if(lfValue.size()+lbValue.size()+ldValue.size()==0) {nsleep(msecs);continue;}
        string rez="";
        bool f=false;
        for(auto& v:lfNotNull) 
            if(*v!=0) {f=true; break;}
        //cout<<f<<endl;
        if(f) {
            for(auto& v:ldValue) {
                if(rez.length()!=0)rez+=",";
                rez+=v.first+"="+to_string(*v.second);
            }
            for(auto& v:lfValue) {
                if(rez.length()!=0)rez+=",";
                rez+=v.first+"="+to_string(*v.second);
            }
            for(auto& v:lbValue) {
                if(rez.length()!=0)rez+=",";
                rez+=v.first+"="+(*v.second?"1":"0");
            }
            rez=DB+",title="+title+" "+rez;
            //printf("[Influx %d] %s\n",rez.length(),rez.c_str());
            //send the message
            if (sendto(s, rez.c_str(), rez.length() , 0 , (struct sockaddr *) &si_other, slen)==-1)
                printf("Error sendto()");
        }
        nsleep(msecs);
	}
    //cout<< "Out while..."<<endl;

	close(s);

    return ;
}
void Influx::add(string name,volatile double* value) {
    ldValue.push_back({name,value});
}
void Influx::add(string name,volatile float* value) {
    lfValue.push_back({name,value});
}
void Influx::add(string name,volatile bool* value){
    lbValue.push_back({name,value});
}
void Influx::addNotNull(volatile float* value){
    lfNotNull.push_back(value);
}
