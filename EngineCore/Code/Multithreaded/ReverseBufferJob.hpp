#pragma once
#ifndef include_REVERSEBUFFERJOB
#define include_REVERSEBUFFERJOB

#include "ThreadedJob.hpp"

class ReverseBufferJob : public ThreadedJob
{
public:
	ReverseBufferJob(char* buffer, size_t bufferSize);

	char* m_sourceBuffer;
	char* m_destinationBuffer;
	size_t m_size;

	virtual void executeJob();
	virtual void callback();
};

#endif