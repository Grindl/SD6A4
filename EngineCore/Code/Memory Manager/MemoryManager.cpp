#include "Debug Tools/ProfileSection.hpp"

#include <cstdlib>
#include "MemoryManager.hpp"

//#define USE_MANUAL_ALLOC

#undef new

MemoryPool g_memoryPool;

void initMemory()
{
	static bool memoryInitialized = false;
	if (!memoryInitialized)
	{
		memoryInitialized = true;
		g_memoryPool = MemoryPool(MEMORY_POOL_SIZE);
	}
}

void PrintLeaks()
{
	g_memoryPool.outputLeaks();
}

void* operator new(size_t objectSizeInBytes)
{
	
#ifdef USE_MANUAL_ALLOC
	initMemory();
	return g_memoryPool.getMemoryBlock(objectSizeInBytes);
#else
	return malloc(objectSizeInBytes);
#endif
	
}

void* operator new(size_t objectSizeInBytes, char* fileName, int lineNum)
{
	
#ifdef USE_MANUAL_ALLOC
	initMemory();
	return g_memoryPool.getMemoryBlock(objectSizeInBytes, fileName, lineNum);
#else
	return malloc(objectSizeInBytes);
#endif
	
}

void* operator new[](size_t objectSizeInBytes)
{
	
#ifdef USE_MANUAL_ALLOC
	initMemory();
	return g_memoryPool.getMemoryBlock(objectSizeInBytes);
#else
	return malloc(objectSizeInBytes);
#endif
	
}

void* operator new[](size_t objectSizeInBytes, char* fileName, int lineNum)
{
	
#ifdef USE_MANUAL_ALLOC
	initMemory();
	return g_memoryPool.getMemoryBlock(objectSizeInBytes, fileName, lineNum);
#else
	return malloc(objectSizeInBytes);
#endif
	
}

void operator delete(void* objectToDelete)
{
	
#ifdef USE_MANUAL_ALLOC
	g_memoryPool.freeMemoryBlock(objectToDelete);
#else
	free(objectToDelete);
#endif
	
}

void operator delete[](void* objectToDelete)
{
	
#ifdef USE_MANUAL_ALLOC
	g_memoryPool.freeMemoryBlock(objectToDelete);
#else
	free(objectToDelete);
#endif
	
}

void operator delete(void* objectToDelete, char* fileName, int lineNum)
{
	
#ifdef USE_MANUAL_ALLOC
	g_memoryPool.freeMemoryBlock(objectToDelete);
#else
	free(objectToDelete);
#endif
	
}
void operator delete[](void* objectToDelete, char* fileName, int lineNum)
{
	
#ifdef USE_MANUAL_ALLOC
	g_memoryPool.freeMemoryBlock(objectToDelete);
#else
	free(objectToDelete);
#endif
	
}

#define new new(__FILE__, __LINE__)