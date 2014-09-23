#pragma once
#ifndef include_JOBMANAGER
#define include_JOBMANAGER

#include <vector>
#include <queue>
#include "ThreadedJob.hpp"
#include "ThreadedWorker.hpp"

/*
2.	Threaded job manager (50 points)
a.	(2 points) Create a JobManager or equivalent class in engine code which can start up zero or more worker threads upon request/initialization;
b.	(2 points) Create a Job or equivalent abstract base class which can be extended by engine or game code;
c.	(2 points) The job manager should support the ability for code to create and schedule Jobs to be performed by the next available worker thread;
d.	(2 points) Jobs can be assigned a priority rating (default is “average”), and higher-priority jobs get handled first (otherwise, first-in/first-out).
e.	(8 points) When a worker thread becomes available, it continuously looks for an available pending job that it can claim.  If an unclaimed pending job 
	is found, it claims and removes the job from the pending list, and executes the Job’s (virtual) Execute() method.  While it is jobless, a worker thread 
	spins in place (perhaps with a Sleep(0) inside its spin loop) – or suspends and waits to be reawakened – until there is a new pending job for it to claim.
f.	(7 points) When a worker thread is finished executing a job, the job is put into a list of completed jobs.  Whenever Update() is called on the JobManager, 
	any completed jobs are removed from the completed job list, and then each of their registered callback events is called in turn.  These calls will therefore 
	be made by the thread that called Update() and the events will be received on his call stack.
g.	(4 points) If zero worker threads exist (at all, not just available worker threads), then the main thread should process (claim, remove, execute, and fire 
	callback event) the single highest priority job in the queue during its Update() method.
h.	(2 points) Lastly, the JobManager should delete a completed Job object once its callback event/function has returned.
i.	(5 points) In general, ALL related code for this assignment must be written in a thread-safe manner; in particular: Job posting, claiming, completion, and 
	removal (as well as thread creation/termination if supported) all need to be thread-safe.
j.	(8 points) At least four concrete implementations of Job are required:
i.	a LoadFileJob or equivalent which can load a named file on disk (or from an archive, per the above requirement) into a byte buffer; and
ii.	a HashBufferJob or equivalent which can generate a hash value for any arbitrarily-sized byte buffer; and
iii.	a ReverseBufferJob or equivalent which will reverse all the bytes in an arbitrarily-sized byte buffer; and
iv.	a SaveFileJob or equivalent which can save an arbitrarily-sized byte buffer to disk.
k.	(8 points) Regardless of whatever jobs your worker thread(s) may be doing at any time, you should demonstrate a smooth 60 Hz visual update onscreen to 
	showcase the dramatically reduced impact on main game thread performance.  Note: in Debug mode, heap memory allocations (new, malloc) and some other operations 
	can cause small “hitches” in performance across all threads; build and run in Release before you assume your threads aren’t working right.
*/

class JobManager
{
public:
	JobManager(int numWorkers = 0);

	std::priority_queue<ThreadedJob*> m_unclaimedJobs;
	std::vector<ThreadedWorker*> m_workers;
	std::vector<ThreadedJob*> m_completedJobs;

	void update();
};


#endif