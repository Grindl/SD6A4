#pragma once
#ifndef include_THREADEDJOB
#define include_THREADEDJOB

enum JobPriority{JOB_LOW, JOB_MEDIUM, JOB_HIGH, JOB_CRITICAL};

class ThreadedJob
{
public:
	ThreadedJob() {}
	ThreadedJob(JobPriority priority) : m_priority(priority) {}

	JobPriority m_priority;

	bool operator<(const ThreadedJob& rhs) const;

	virtual void executeJob() = 0;
	virtual void callback() = 0;
	
};

inline bool ThreadedJob::operator<(const ThreadedJob& rhs) const
{
	return m_priority < rhs.m_priority;
}


#endif