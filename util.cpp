#include "util.h"


bool cmp(char* str1,char* str2) {
    unsigned index=0;
    while(true) {
        if(str1[index]==0 && str2[index]==0) return true;
        if(str1[index]!=str2[index]) return false;
        index++;
    }
}
bool cmp(char* str1,char* str2, unsigned len) {
    unsigned index=0;
    while(true) {
        if(index>=len) return true;
        if(str1[index]==0 && str2[index]==0) return true;
        if(str1[index]!=str2[index]) return false;
        index++;
    }
}

int nsleep(long miliseconds)
{
    struct timespec req, rem;
    if(miliseconds > 999) {
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
    }
    else {
        req.tv_sec = 0;                         /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
    }
    return nanosleep(&req , &rem);
}

void msleep(unsigned int millis)
{
    struct timespec sleeper;
    sleeper.tv_sec = (time_t)(millis / 1000);
    sleeper.tv_nsec = (time_t)(millis % 1000) * 1000000;
    nanosleep(&sleeper, NULL);
}

int kb_hit (void) {
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);
    select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

void change_mode_kbhint(int dir) {
    static struct termios oldt, newt;

    if ( dir == 1 ) {
        tcgetattr( STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    }
    else
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

float flin2(float x, float x1, float y1, float x2, float y2) {
    float rez=(x - x1) * (y2 - x2) / (y1 - x1) + x2;
    if(x2<y2) {
        if(rez<x2)rez=x2;
        if(rez>y2)rez=y2;
    }
    else
    {
        if(rez>x2)rez=x2;
        if(rez<y2)rez=y2;
    }
    return rez;
}

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void SentToBot(string id, string message) {
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Error create UDP socket");
		return ;
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(8080);

	if (inet_aton("192.168.150.137" , &si_other.sin_addr) == 0)
	{
		printf("inet_aton() failed");
		return ;
	}
	std::string rez="";
	rez="{\"id\":\""+id+"\",\"msg\":\""+message+"\"}";
	printf("[Telegram %d] %s\n",rez.length(),rez.c_str());
	//send the message
    int numBytes=sendto(s, rez.c_str(), rez.length() , 0 , (struct sockaddr *) &si_other, slen);
	if (numBytes==-1)
		printf("Error sendto()");
    printf("Sent %d bytes\n",numBytes);
	close(s);

    return ;
}
