#include <process.h>

#include "ThreadedWorker.hpp"

#include "Memory Manager/MemoryManager.hpp"

//DEPRECATED but left in for the sake of CreateThread
DWORD __stdcall InitWorkerThread_stdcall(LPVOID lpThreadParameter)
{
	ThreadedWorker* owningWorker = (ThreadedWorker*) lpThreadParameter;
	owningWorker->update();
	return 0;
}

void InitWorkerThread(void* parameter)
{
	ThreadedWorker* owningWorker = (ThreadedWorker*) parameter;
	owningWorker->update();
}


ThreadedWorker::ThreadedWorker()
	:m_state(WORKER_IDLE)
	,m_job(nullptr)
{
	_beginthread(InitWorkerThread, 0, this);
}

ThreadedWorker::ThreadedWorker(int ID)
	:m_workerID(ID)
	,m_state(WORKER_IDLE)
	,m_job(nullptr)
{
	_beginthread(InitWorkerThread, 0, this);
}

void ThreadedWorker::update()
{
	while (true)
	{
		if (m_state == WORKER_WORKING)
		{
			m_job->executeJob();
			m_state = WORKER_DONE;
		}
		
		Sleep(0);
	}
}
