#ifndef _WORKERLOOP_H_
#define _WORKERLOOP_H_

#include "Worker.h";

class WorkerLoop
{
private:
	Worker **_workers;
	int _maxWorkers;
	int _workerCount;

public:
	WorkerLoop(int maxWorkers);
	~WorkerLoop();
	void AddWorker(Worker *worker);
	void RemoveWorker(Worker *worker);
	void Update();
};

#endif
