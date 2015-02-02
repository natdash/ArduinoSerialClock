#ifndef _CLOCKALARM_H_
#define _CLOCKALARM_H_

#include "Arduino.h"
#include "Time.h"

const int MESSAGE_LENGTH = 17;

class ClockAlarm
{
private:
	time_t _time;
	char _message[MESSAGE_LENGTH];
	void FillSpaces(char *buffer, int length);

public:
	ClockAlarm(time_t time, const char *message);
	~ClockAlarm();

	time_t GetTime();
	char *GetMessage();
};

#endif
