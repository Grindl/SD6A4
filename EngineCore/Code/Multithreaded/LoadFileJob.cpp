#include "LoadFileJob.hpp"
#include "..\Event System\EventSystemHelper.hpp"
#include "..\Event System\NamedProperties.hpp"

#include "Memory Manager/MemoryManager.hpp"

LoadFileJob::LoadFileJob()
{

}
LoadFileJob::LoadFileJob(std::string fileName) 
	: m_fileName(fileName)
	, ThreadedJob(JOB_MEDIUM)
{

}

void LoadFileJob::executeJob()
{
	FILE* fileIn = fopen(m_fileName.c_str(), "rb");
	fseek(fileIn, 0, SEEK_END);
	int fileSizeInBytes = (int)ftell(fileIn);
	rewind(fileIn);
	m_loadedFile = new char[fileSizeInBytes];
	fread(m_loadedFile, sizeof(char), fileSizeInBytes, fileIn);
	fclose(fileIn);
}

void LoadFileJob::callback()
{
	std::string eventName = "LoadFileJob Complete ";
	eventName += m_fileName;
	NamedProperties data = NamedProperties();
	NamedProperties::NamedHelper<char*> fileData;
	fileData.val = &m_loadedFile;
	data.addProperty(eventName, &fileData);
	fireEventGlobal(eventName);

}
