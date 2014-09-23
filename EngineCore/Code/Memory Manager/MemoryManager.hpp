#pragma once
#ifndef include_MEMORYMANAGER
#define include_MEMORYMANAGER


#include "MemoryPool.hpp"


#undef new

extern MemoryPool g_memoryPool;
void initMemory();
void PrintLeaks();

//#define ANT_RESTRICTION

#ifdef ANT_RESTRICTION
static const size_t MEMORY_POOL_SIZE = 60000000;
#else
static const size_t MEMORY_POOL_SIZE = 500000000; //.5 GBi
#endif

void* operator new(size_t objectSizeInBytes);
void* operator new(size_t objectSizeInBytes, char* fileName, int lineNum);

void* operator new[](size_t objectSizeInBytes);
void* operator new[](size_t objectSizeInBytes, char* fileName, int lineNum);

void operator delete(void* objectToDelete);
void operator delete[](void* objectToDelete);

void operator delete(void* objectToDelete, char* fileName, int lineNum);
void operator delete[](void* objectToDelete, char* fileName, int lineNum);


#define new new(__FILE__, __LINE__)

#endif