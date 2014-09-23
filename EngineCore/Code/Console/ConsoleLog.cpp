#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>


#include "..\Rendering\OpenGLFunctions.hpp"
#include "ConsoleLog.hpp"

#include "Memory Manager/MemoryManager.hpp"

int ConsoleLog::s_currentOffset = 0;
std::string* ConsoleLog::s_logText = 0;

ConsoleLog::ConsoleLog()
{
	ConsoleLog::s_currentOffset = 0;
	m_fontRenderer = FontRenderer();
	ConsoleLog::s_logText = m_logText;
}


void ConsoleLog::render()
{
	//TODO move this height of rows and other constants to someplace nicer
	float heightOfRows = HEIGHT_OF_LOG/ROWS_TO_DISPLAY_ON_SCREEN;

	for(int ii = 0; ii < ROWS_TO_DISPLAY_ON_SCREEN && ii < ConsoleLog::s_currentOffset; ii++)
	{
		Vector3f startLocationForLine = Vector3f(0.f, (ii+2)*heightOfRows, 0.f);
		m_fontRenderer.drawString(startLocationForLine, m_logText[ii]);
	}
}

void ConsoleLog::appendLine(std::string lineToBeAppended)
{
	//TODO make this more robust and use a circular buffer
	m_logText[ConsoleLog::s_currentOffset] = lineToBeAppended;
	ConsoleLog::s_currentOffset++;
	if(ConsoleLog::s_currentOffset > SIZE_OF_LOG)
	{
		ConsoleLog::s_currentOffset = 0;
	}
}

void ConsoleLog::GlobalAppendLine(std::string lineToBeAppended)
{
	ConsoleLog::s_logText[ConsoleLog::s_currentOffset] = lineToBeAppended;
	ConsoleLog::s_currentOffset++;
	if(ConsoleLog::s_currentOffset > SIZE_OF_LOG)
	{
		ConsoleLog::s_currentOffset = 0;
	}
}