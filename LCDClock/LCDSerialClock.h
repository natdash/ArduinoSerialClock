#ifndef _LCDSerialClock_H_
#define _LCDSerialClock_H_

#include <Time.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "ClockDefs.h"
#include "ClockAlarm.h"
#include "ClockAVIFace.h"

#include "WorkerLoop.h"
#include "ClockDisplayTime.h"
#include "ClockMessageController.h"

class LCDSerialClock
{
private:
	ClockAlarm **_alarms;
	int _totalAlarms;
	int _alarmCount;
	time_t _timeZoneOffset;
	time_t _lastSync;

	ClockAVIFace *_clockAVIFace;
	WorkerLoop *_workerLoop;
	LiquidCrystal _lcd;
	ClockMessageController *_clockMessageController;

	time_t ParseSerialTimestamp(const char *command);

	void WriteTime();
	void ReadTime(const char *command);
	void ReadAlarm(char *command);
	void WriteAlarm();
	void ReadTimeZone(const char *command);

	void RequestTime();

	void CheckAlarm();

	void RemoveAlarm(ClockAlarm *oldAlarm);
	void DeleteAlarm(ClockAlarm *oldAlarm);

	int ReadButton(unsigned int button);


public:
	LCDSerialClock(int totalAlarms, int *lcdPins);
	~LCDSerialClock();

	void SetTimeZone(time_t hours, time_t minutes);
	void ProcessSerial();
	void UpdateDisplay();
	void CheckSync();

	void SetAlarm(time_t time, const char* message);
	void SetTime(time_t time);

	void CheckInput();
};

#endif
