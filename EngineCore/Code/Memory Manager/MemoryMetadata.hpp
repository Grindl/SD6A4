#pragma once
#ifndef include_MEMORYMETADATA
#define include_MEMORYMETADATA


class MemoryMetadata
{
public:
	//MemoryMetadata();
	MemoryMetadata(size_t lengthOfBlock = 0, bool isOccupied = true, int allocatingLine = -1, char* allocatingFileName = "INVALID", size_t lengthOfPreviousBlock = 0);

	size_t m_lengthOfBlock;
	size_t m_lengthOfPreviousBlock;
	bool m_isOccupied;
	int m_allocatingLine;
	char* m_allocatingFileName;
};

#endif