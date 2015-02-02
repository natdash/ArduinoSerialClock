#include "Arduino.h"
#include "LCDSerialClock.h"

LCDSerialClock::LCDSerialClock(int totalAlarms, int *lcdPins)
	: _totalAlarms(totalAlarms),
	  _alarmCount(0),
	  _timeZoneOffset(0),
	  _lastSync(0),
	  _lcd(lcdPins[0], lcdPins[1], lcdPins[2], lcdPins[3], lcdPins[4], lcdPins[5])
{
	_alarms = new ClockAlarm *[totalAlarms];

	pinMode(BACKLIGHT_PIN,OUTPUT);

	_clockAVIFace = new ClockAVIFace(&_lcd);
	_workerLoop = new WorkerLoop(10);

	ClockDisplayTime *displayTimeWorker = new ClockDisplayTime(_clockAVIFace);
	_workerLoop->AddWorker(displayTimeWorker);

	_clockMessageController = new ClockMessageController(_clockAVIFace, totalAlarms, _workerLoop);
	_workerLoop->AddWorker(_clockMessageController);
}

LCDSerialClock::~LCDSerialClock()
{
	for(int i = 0; i < _alarmCount; i++)
		delete _alarms[i];
	delete [] _alarms;
	delete _clockAVIFace;
	delete _clockMessageController;
}

time_t LCDSerialClock::ParseSerialTimestamp(const char *command)
{
	time_t time = 0;
	command++;
	while (*command)
	{
	    char c = *command;
	    if (c >= '0' && c <= '9')
	    	time = (10 * time) + (c - '0');
	    command++;
	}
	return time + _timeZoneOffset;
}

void LCDSerialClock::SetTimeZone(unsigned long hours, unsigned long minutes)
{
	time_t timeZone = _timeZoneOffset;
	_timeZoneOffset = (hours * 3600) + (minutes * 60);
	time_t tzDiff = _timeZoneOffset - timeZone;
	setTime(now() + tzDiff);
}

void LCDSerialClock::ProcessSerial()
{
	char buffer[50] = "";
	char *command = buffer;
	int i = 0;

	while(command[i - 1] != '\n')
	{
		if (Serial.available())
			command[i++] = Serial.read();
	}
	command[i - 1] = '\0';

	switch(command[0])
	{
	case SET_TIME:
		ReadTime(command);
		break;

	case WRITE_TIME:
		WriteTime();
		break;

	case SET_ALARM:
		ReadAlarm(command);
		break;

	case WRITE_ALARM:
		WriteAlarm();
		break;

	case SET_TIMEZONE:
		ReadTimeZone(command);
		break;
	}
}

void LCDSerialClock::UpdateDisplay()
{
	CheckAlarm();
	_workerLoop->Update();
}

void LCDSerialClock::CheckSync()
{
	if(((now() - _lastSync) > SYNC_PERIOD) || _lastSync == 1) {
		Serial.println(now() - _lastSync);
		RequestTime();
	}
}

void LCDSerialClock::CheckAlarm()
{
	for(int i = 0; i < _alarmCount; i++)
	{
		if(now() == _alarms[i]->GetTime())
		{
			_clockMessageController->AddAlarm(_alarms[i]);
			RemoveAlarm(_alarms[i]);
		}
	}
}

void LCDSerialClock::RemoveAlarm(ClockAlarm *oldAlarm)
{
	int i = 0;
	for(; i < _alarmCount; i++)
	{
		if(oldAlarm == _alarms[i])
			break;
	}
	if(i < _alarmCount)
	{
		i++;
		for(; i < _alarmCount; i++)
			_alarms[i - 1] = _alarms[i];
		_alarmCount--;
	}

}

void LCDSerialClock::DeleteAlarm(ClockAlarm *oldAlarm)
{
	int i = 0;
	for(; i < _alarmCount; i++)
	{
		if(oldAlarm == _alarms[i])
			break;
	}
	delete _alarms[i];
	i++;
	for(; i < _alarmCount; i++)
	{
		_alarms[i - 1] = _alarms[i];
	}
	_alarmCount--;
}

void LCDSerialClock::WriteTime()
{
	Serial.print(now(), DEC);
}

void LCDSerialClock::ReadTime(const char *command)
{
	SetTime(ParseSerialTimestamp(command));
}

void LCDSerialClock::ReadAlarm(char *command)
{

	char* buffer = command;
	char* timestamp = strtok(buffer, "|");
	char* message = strtok(NULL, "|");
	Serial.println(timestamp);
	Serial.println(message);
	SetAlarm(ParseSerialTimestamp(timestamp), message);
}

void LCDSerialClock::WriteAlarm()
{
	for(int i = 0; i < _alarmCount; i++)
	{
		Serial.println(_alarms[i]->GetTime(),DEC);
	}
}

time_t d2toa(const char *chars)
{
	return (((chars[0] - '0') * 10) + chars[1] - '0');
}

void LCDSerialClock::ReadTimeZone(const char *command)
{
	SetTimeZone(d2toa(command + 1), d2toa(command + 3));
}

void LCDSerialClock::SetAlarm(time_t time, const char* message)
{
	if (_alarmCount < _totalAlarms)
		_alarms[_alarmCount++] = new ClockAlarm(time, message);

}

void LCDSerialClock::SetTime(time_t time)
{
	setTime(time);
	_lastSync = time;
}

void LCDSerialClock::RequestTime()
{
	Serial.println(REQUEST_TIME);
}

void LCDSerialClock::CheckInput()
{
	unsigned int buttonSignal = analogRead(INPUT_PIN);
	int button = ReadButton(buttonSignal);

	switch(button)
	{
		case BUTTON_SELECT:
			_clockMessageController->FlushAlarms();
	}
}

int LCDSerialClock::ReadButton(unsigned int button)
{
	int btn = BUTTON_NONE;
	if(button < (BUTTON_SIGNAL_RIGHT + BUTTON_SIGNAL_ERROR))
		btn = BUTTON_RIGHT;
	else if(button > (BUTTON_SIGNAL_UP - BUTTON_SIGNAL_ERROR)
			&& button < (BUTTON_SIGNAL_UP + BUTTON_SIGNAL_ERROR))
		btn = BUTTON_UP;
	else if(button > (BUTTON_SIGNAL_DOWN - BUTTON_SIGNAL_ERROR)
			&& button < (BUTTON_SIGNAL_DOWN + BUTTON_SIGNAL_ERROR))
		btn = BUTTON_DOWN;
	else if(button > (BUTTON_SIGNAL_LEFT - BUTTON_SIGNAL_ERROR)
			&& button < (BUTTON_SIGNAL_LEFT + BUTTON_SIGNAL_ERROR))
		btn = BUTTON_LEFT;
	else if(button > (BUTTON_SIGNAL_SELECT - BUTTON_SIGNAL_ERROR)
			&& button < (BUTTON_SIGNAL_SELECT + BUTTON_SIGNAL_ERROR))
		btn = BUTTON_SELECT;

	return btn;
}


