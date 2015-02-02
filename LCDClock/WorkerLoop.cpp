#include "WorkerLoop.h"

WorkerLoop::WorkerLoop(int maxWorkers)
	:
	_maxWorkers(maxWorkers),
	_workerCount(0)
{
	_workers = new Worker *[_maxWorkers];
}

WorkerLoop::~WorkerLoop()
{
	for(int i = 0;i < _workerCount; i++)
		delete _workers[i];
	delete[] _workers;
}

void WorkerLoop::AddWorker(Worker *worker)
{
	if(_workerCount < _maxWorkers)
		_workers[_workerCount++] = worker;
}

void WorkerLoop::RemoveWorker(Worker *worker)
{
	int i = 0;
	for(; i < _workerCount; i++)
	{
		if(_workers[i] == worker)
		{
			delete _workers[i];
			break;
		}
	}
	if(i < _workerCount)
	{
		i++;
		for(; i < _workerCount; i++)
			_workers[i-1] = _workers[i];
		_workerCount--;
	}
}

void WorkerLoop::Update()
{
	for(int i = 0; i < _workerCount; i++)
	{
		if(!_workers[i]->Update())
		{
			RemoveWorker(_workers[i]);
			i--;
		}
	}
}
