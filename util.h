#pragma once

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <time.h>   /* Needed for struct timespec */
#include <stdbool.h>
#include <sys/file.h>
#include <stdarg.h>
#include <chrono>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int nsleep(long miliseconds);
void msleep(unsigned int millis);

int kb_hit (void);
void change_mode_kbhint(int dir);

float flin2(float x, float x1, float x2, float y1, float y2);
bool cmp(char* str1,char* str2);
bool cmp(char* str1,char* str2, unsigned len);
uint64_t timeSinceEpochMillisec();
void SentToBot(string id, string message);
