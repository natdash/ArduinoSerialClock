#include "Worker.h"

Worker::Worker(Worker *syncWorker)
	:
	_nextWorkTime(0)
{
	if(syncWorker)
	{
		_nextWorkTime = syncWorker->GetNextWorkTime();
	}
//	DoWork();
}

Worker::~Worker()
{

}

void Worker::SetNextWorkTime(time_t deltaTime)
{
	_nextWorkTime += deltaTime;
}

bool Worker::Update()
{
	if (_nextWorkTime == 0)
		_nextWorkTime = millis();
	time_t currentTime = millis();
	if(currentTime >= _nextWorkTime)
		return DoWork();
	else
		return true;
}

time_t Worker::GetNextWorkTime()
{
	return _nextWorkTime;
}
