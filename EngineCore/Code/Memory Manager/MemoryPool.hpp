#pragma once
#ifndef include_MEMORYPOOL
#define include_MEMORYPOOL


class MemoryPool
{
public:
	MemoryPool(){}
	MemoryPool(size_t poolSize);

	size_t m_sizeOfPool;
	size_t m_endBlockStart;
	size_t m_firstOpenBlock;
	char* m_pool;

	void* getMemoryBlock(size_t sizeOfRequiredBlock);
	void* getMemoryBlock(size_t sizeOfRequiredBlock, char* fileName, int lineNum);
	void freeMemoryBlock(void* objectToDelete);
	void outputLeaks();
};


#endif