#ifndef _WORKER_H_
#define _WORKER_H_

#include "Arduino.h"
#include "Time.h"

class Worker
{
private:
	time_t	_nextWorkTime;

protected:
	Worker(Worker *syncWorker = 0);
	void SetNextWorkTime(time_t deltaTime);
	virtual bool DoWork() = 0;

public:
	bool Update();
	virtual ~Worker();
	time_t GetNextWorkTime();
};

#endif
