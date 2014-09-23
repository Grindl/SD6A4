#pragma once
#ifndef include_HASHBUFFERJOB
#define include_HASHBUFFERJOB

#include <string>
#include "ThreadedJob.hpp"

class HashBufferJob : public ThreadedJob
{
public:
	HashBufferJob(char* buffer, size_t bufferSize);

	char* m_sourceBuffer;
	size_t m_size;
	int m_hash;

	virtual void executeJob();
	virtual void callback();
};

#endif