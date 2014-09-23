#include <functional>
#include <bitset>

#include "HashBufferJob.hpp"
#include "..\Event System\EventSystemHelper.hpp"
#include "..\Event System\NamedProperties.hpp"

#include "Memory Manager/MemoryManager.hpp"

HashBufferJob::HashBufferJob(char* buffer, size_t bufferSize)
	:ThreadedJob(JOB_MEDIUM)
	,m_sourceBuffer(buffer)
	,m_size(bufferSize)
{

}

void HashBufferJob::executeJob()
{
	//size_t numBits = m_size * sizeof(char);
	//std::bitset<numBits> bitsetCast = std::bitset<numBits>(&)
	std::hash<char*> intermediateHash;
	m_hash =  intermediateHash(m_sourceBuffer);
	//std::hash<std::bitset<numBits>> bitsetHash;
	//bitsetHash()
}

void HashBufferJob::callback()
{
	std::string eventName = "HashBufferJob Complete";
	NamedProperties data = NamedProperties();
	NamedProperties::NamedHelper<int> bufferData;
	bufferData.val = &m_hash;
	data.addProperty(eventName, &bufferData);
	fireEventGlobal(eventName);
}
