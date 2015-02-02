#include "ClockMessageController.h"

ClockMessageController::ClockMessageController(ClockAVIFace *clockAVIFace, int totalAlarms, WorkerLoop *workerLoop)
	:
	_clockAVIFace(clockAVIFace),
	_workerLoop(workerLoop),
	_clockBacklightFlash(0),
	_currentAlarmCount(0),
	_currentDisplayMessage(0),
	_totalAlarms(totalAlarms)
{
	_currentAlarms = new ClockAlarm *[totalAlarms];
}

ClockMessageController::~ClockMessageController()
{
	for(int i = 0; i < _currentAlarmCount; i++)
		delete _currentAlarms[i];
	delete[] _currentAlarms;
}

bool ClockMessageController::DoWork()
{
	if (_currentAlarmCount == 0)
		_clockAVIFace->DisplayDateLine();
	else
		DisplayMessage();

	SetNextWorkTime(1000);
	return true;
}

void ClockMessageController::AddAlarm(ClockAlarm *newAlarm)
{
	if (_currentAlarmCount < _totalAlarms)
	{
		_currentAlarms[_currentAlarmCount++] = newAlarm;
		if(_currentAlarmCount == 1)
		{
			_clockBacklightFlash = new ClockBacklightFlash(_clockAVIFace, this);
			_workerLoop->AddWorker(_clockBacklightFlash);
		}
	}
}

void ClockMessageController::FlushAlarms()
{
	for(int i = 0; i < _currentAlarmCount; i++)
		delete _currentAlarms[i];
	_workerLoop->RemoveWorker(_clockBacklightFlash);
	_clockBacklightFlash = 0;
	_currentAlarmCount = 0;
	_currentDisplayMessage = 0;
}

void ClockMessageController::DisplayMessage()
{
	if(_currentDisplayMessage < _currentAlarmCount)
	{
		char *message = _currentAlarms[_currentDisplayMessage]->GetMessage();
		_clockAVIFace->SetLCDLineText(message, 0);
		_currentDisplayMessage++;
	}
	else
	{
		_clockAVIFace->DisplayDateLine();
		_currentDisplayMessage = 0;
	}
}

