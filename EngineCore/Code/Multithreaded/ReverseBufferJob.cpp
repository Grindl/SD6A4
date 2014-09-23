#include "ReverseBufferJob.hpp"

#include "..\Event System\EventSystemHelper.hpp"
#include "..\Event System\NamedProperties.hpp"

#include "Memory Manager/MemoryManager.hpp"


ReverseBufferJob::ReverseBufferJob(char* buffer, size_t bufferSize)
	:ThreadedJob(JOB_MEDIUM)
	,m_sourceBuffer(buffer)
	,m_size(bufferSize)
{

}

void ReverseBufferJob::executeJob()
{
	m_destinationBuffer = new char[m_size];
	for (unsigned int bufferIndex = 0; bufferIndex < m_size; bufferIndex++)
	{
		m_destinationBuffer[m_size - (bufferIndex+1)] = m_sourceBuffer[bufferIndex];
	}
}

void ReverseBufferJob::callback()
{
	std::string eventName = "HashBufferJob Complete";
	NamedProperties data = NamedProperties();
	NamedProperties::NamedHelper<char*> bufferData;
	bufferData.val = &m_destinationBuffer;
	data.addProperty(eventName, &bufferData);
	fireEventGlobal(eventName);
}