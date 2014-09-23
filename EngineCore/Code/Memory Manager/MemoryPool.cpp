#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "MemoryPool.hpp"
#include "MemoryMetadata.hpp"
#include <cstdlib>
#include <sstream>
//#include <io.h>
//#include <iostream>

#undef new

MemoryPool::MemoryPool(size_t poolSize)
	:m_sizeOfPool(poolSize)
{
	m_pool = (char*)malloc(m_sizeOfPool*sizeof(char));
	MemoryMetadata* currentMetadata = reinterpret_cast<MemoryMetadata*>(m_pool);
	currentMetadata->m_isOccupied = false;
	currentMetadata->m_lengthOfBlock = m_sizeOfPool;
	m_endBlockStart = 0;
	m_firstOpenBlock = 0;
}

void* MemoryPool::getMemoryBlock(size_t sizeOfRequiredBlock)
{
	return getMemoryBlock(sizeOfRequiredBlock, "INVALID", -1);
}

void* MemoryPool::getMemoryBlock(size_t sizeOfRequiredBlock, char* fileName, int lineNum)
{
	if (sizeOfRequiredBlock < 1)
	{
		int DANGERBREAK = 1;
	}
	void* returnPtr = 0;
	bool spaceFound = false;
	size_t currentOffset = 0;
	size_t previousOffset = currentOffset;
	size_t totalRequiredSize = sizeOfRequiredBlock + sizeof(MemoryMetadata);
	MemoryMetadata myMetadata = MemoryMetadata(totalRequiredSize, true, lineNum, fileName);
	while(!spaceFound && currentOffset + totalRequiredSize < m_sizeOfPool)
	{
		MemoryMetadata* currentMetadata = reinterpret_cast<MemoryMetadata*>(m_pool+currentOffset);
		if (!currentMetadata->m_isOccupied && currentMetadata->m_lengthOfBlock >= totalRequiredSize)
		{
			spaceFound = true;
			size_t originalSize = currentMetadata->m_lengthOfBlock;
			size_t remainingSize = currentMetadata->m_lengthOfBlock - totalRequiredSize;
			*currentMetadata = myMetadata;
			MemoryMetadata* previousMetadata = reinterpret_cast<MemoryMetadata*>(m_pool+previousOffset);
			currentMetadata->m_lengthOfPreviousBlock = previousMetadata->m_lengthOfBlock;
			returnPtr = m_pool+currentOffset+sizeof(MemoryMetadata);
			if (remainingSize >= sizeof(MemoryMetadata))
			{
				MemoryMetadata* bookendedMetadata = reinterpret_cast<MemoryMetadata*>(m_pool+currentOffset+totalRequiredSize);
				MemoryMetadata nextMetadata = MemoryMetadata(remainingSize, false);
				*bookendedMetadata = nextMetadata;
				bookendedMetadata->m_lengthOfPreviousBlock = totalRequiredSize;
			}
			else
			{
				currentMetadata->m_lengthOfBlock = originalSize;
			}
		}
		
		if (currentMetadata->m_lengthOfBlock == 0)
		{
			int DANGERBREAK = 1;
		}
		if (currentMetadata->m_lengthOfBlock > m_sizeOfPool)
		{
			int DANGERBREAK = 1;
		}
		previousOffset = currentOffset;
		currentOffset+= currentMetadata->m_lengthOfBlock;
		if (currentOffset < 0)
		{
			int DANGERBREAK = 1;
		}
	}
	return returnPtr;
}

void MemoryPool::freeMemoryBlock(void* objectToDelete)
{
	if (objectToDelete > m_pool && objectToDelete < m_pool + m_sizeOfPool)
	{
		char* memOffset = reinterpret_cast<char*>(objectToDelete);
		memOffset -= sizeof(MemoryMetadata);
		MemoryMetadata* metadataOfObject = reinterpret_cast<MemoryMetadata*>(memOffset);
		metadataOfObject->m_isOccupied = false;
		if(memOffset+metadataOfObject->m_lengthOfBlock < m_pool+m_sizeOfPool)
		{
			char* nextBlock = memOffset + metadataOfObject->m_lengthOfBlock;
			MemoryMetadata* metadataOfNext = reinterpret_cast<MemoryMetadata*>(nextBlock);
			if (!metadataOfNext->m_isOccupied)
			{
				metadataOfObject->m_lengthOfBlock += metadataOfNext->m_lengthOfBlock;
			}
		}
		if (memOffset != m_pool)
		{
			size_t previousOffset = (size_t)memOffset - metadataOfObject->m_lengthOfPreviousBlock;
			MemoryMetadata* metadataOfPrevious = reinterpret_cast<MemoryMetadata*>(m_pool+previousOffset);
			//while(metadataOfCurrent->m_lengthOfBlock + currentOffset < targetOffset)
			//{
			//	previousOffset = currentOffset;
			//	currentOffset += metadataOfCurrent->m_lengthOfBlock;
			//	metadataOfCurrent = reinterpret_cast<MemoryMetadata*>(m_pool+ currentOffset);
			//
			//}
			//MemoryMetadata* metadataOfPrevious = reinterpret_cast<MemoryMetadata*>(m_pool + previousOffset);
			if (!metadataOfPrevious->m_isOccupied)
			{
				metadataOfPrevious->m_lengthOfBlock += metadataOfObject->m_lengthOfBlock;
			}
		}
	}
	else
	{
		free(objectToDelete);
	}
}

void MemoryPool::outputLeaks()
{
	size_t currentOffset = 0;
	while (currentOffset < m_sizeOfPool)
	{
		MemoryMetadata* currentMetadata = reinterpret_cast<MemoryMetadata*>(m_pool+currentOffset);
		if (currentMetadata->m_isOccupied)
		{
			std::stringstream outputString;
			outputString<<currentMetadata->m_allocatingFileName<<"("<<currentMetadata->m_allocatingLine<<"): Memory Leak Detected at line "<<currentMetadata->m_allocatingLine<<" of size "<<currentMetadata->m_lengthOfBlock<<"\n";
			OutputDebugStringA(outputString.str().c_str());
			//std::cout<<outputString<<std::endl;
		}
		currentOffset+=currentMetadata->m_lengthOfBlock;
	}
	//std::cout<<"Mem"<<std::endl;
}

#define new new(__FILE__, __LINE__)