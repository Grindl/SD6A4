#include "MemoryMetadata.hpp"

MemoryMetadata::MemoryMetadata(size_t lengthOfBlock /* = 0 */, bool isOccupied /* = true */, int allocatingLine /* = -1 */, char* allocatingFileName /* = "INVALID" */, size_t lengthOfPreviousBlock)
	:m_lengthOfBlock(lengthOfBlock)
	,m_isOccupied(isOccupied)
	,m_allocatingLine(allocatingLine)
	,m_allocatingFileName(allocatingFileName)
	,m_lengthOfPreviousBlock(lengthOfPreviousBlock)
{

}