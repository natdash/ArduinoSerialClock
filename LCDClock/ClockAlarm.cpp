#include "ClockAlarm.h"

ClockAlarm::ClockAlarm(time_t time, const char *message)
{
	_time = time;
	_message[0] = '\0';
	strcat(_message,message);
	FillSpaces(_message,(MESSAGE_LENGTH - 1));
}

ClockAlarm::~ClockAlarm()
{

}

time_t ClockAlarm::GetTime()
{
	return _time;
}

char *ClockAlarm::GetMessage()
{
	return _message;
}

void ClockAlarm::FillSpaces(char *buffer, int length)
{
	int i = 0;
	while(buffer[i] != '\0')
		i++;
	for(; i < length; i++)
		buffer[i] = ' ';
	buffer[i] = '\0';
}
