#include "IOHandler.hpp"

#include "Memory Manager/MemoryManager.hpp"

//TODO: this class

//----------------------------------------------------------------------------------------
IOHandler::IOHandler()
{
	for (int ii = 0; ii < 256; ii++)
	{
		m_keyIsDown[ii] = false;
	}
}

//----------------------------------------------------------------------------------------
bool IOHandler::KeyDownEvent(unsigned char asKey)
{
	m_keyIsDown[asKey] = true;
	return false;
}

//----------------------------------------------------------------------------------------
bool IOHandler::KeyUpEvent(unsigned char asKey)
{
	m_keyIsDown[asKey] = false;
	return false;
}