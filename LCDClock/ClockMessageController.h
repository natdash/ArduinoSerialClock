#ifndef _CLOCKDISPLAYMESSAGE_H_
#define _CLOCKDISPLAYMESSAGE_H_

#include <Time.h>

#include "Worker.h"
#include "WorkerLoop.h"
#include "ClockAVIFace.h"
#include "ClockAlarm.h"
#include "ClockBacklightFlash.h"

class ClockMessageController : public Worker
{
private:
	ClockAVIFace *_clockAVIFace;
	ClockAlarm **_currentAlarms;
	WorkerLoop *_workerLoop;
	ClockBacklightFlash *_clockBacklightFlash;
	int _currentAlarmCount;
	int _currentDisplayMessage;
	int _totalAlarms;

	void DisplayMessage();

public:
	ClockMessageController(ClockAVIFace *clockAVIFace, int totalAlarms, WorkerLoop* _workerLoop);
	~ClockMessageController();
	bool DoWork();

	void AddAlarm(ClockAlarm *newAlarm);
	void FlushAlarms();
};

#endif
