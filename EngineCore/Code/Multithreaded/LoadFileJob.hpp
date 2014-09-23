#pragma once
#ifndef include_LOADFILEJOB
#define include_LOADFILEJOB

#include <string>
#include "ThreadedJob.hpp"

class LoadFileJob : public ThreadedJob
{
public:
	LoadFileJob();
	LoadFileJob(std::string fileName);

	std::string m_fileName;
	char* m_loadedFile;


	virtual void executeJob();
	virtual void callback();
};

#endif