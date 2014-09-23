#pragma once
#ifndef include_THREADEDWORKER
#define include_THREADEDWORKER

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ThreadedJob.hpp"

enum WorkerState{WORKER_IDLE, WORKER_WORKING, WORKER_DONE};

class ThreadedWorker
{
public:
	ThreadedWorker();
	ThreadedWorker(int ID);

	WorkerState m_state;
	ThreadedJob* m_job;
	int m_workerID;

	void update();
};


#endif