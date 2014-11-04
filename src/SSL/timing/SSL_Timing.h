#ifndef SSL_TIMING_H_
#define SSL_TIMING_H_

extern int uptime;
extern double delta;
extern double fps;
extern double tick;

extern int canTick;

void SSL_Timer_Init();

#endif
