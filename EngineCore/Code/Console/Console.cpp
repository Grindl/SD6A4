#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "..\Rendering\OpenGLFunctions.hpp"
#include <string>

#include "CommandParser.hpp"
#include "Console.hpp"

#include "Memory Manager/MemoryManager.hpp"

bool calcLength(std::string arguments)
{

	char stringBuffer[255];
	float lenghtOfArgument = FontRenderer::CalcTextWidth(arguments, 20.f);
	sprintf(stringBuffer, "The length of the argument was %f", lenghtOfArgument);

	ConsoleLog::GlobalAppendLine(stringBuffer);
	return true;
}

Console::Console()
{
	m_currentTextOffset = 0;
	m_log = ConsoleLog();
	CommandParser::RegisterCommand("calcLength", calcLength);
}

void Console::render()
{
	//HACK fixing bad pointers
	FontRenderer::s_fallbackFont = &(m_log.m_fontRenderer.m_fontToUse);
	ConsoleLog::s_logText = (m_log.m_logText);


	std::string commandAsString = std::string();
	for(unsigned int ii = 0; ii < m_command.size(); ii++)
	{
		commandAsString.append(1, m_command[ii]);
	}
	std::string commandBeforeCursor = commandAsString.substr(0,m_currentTextOffset);
	//HACK hardcoded cursor length
	float positionOfCursor = FontRenderer::CalcTextWidth(commandBeforeCursor, 20.f);

	//TODO figure out why it is necessary to disable depth test
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	//HACK hardcoded values
	glOrtho(1.0, 1024.0, 1.0, 1024.0/(16.0/9.0), 0, 1);
	//TODO potentially use the shaders, also these two lines are essentially duplicated within draw string, but better safe
	glUseProgram(0);

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	{
		glColor4f(0.f, 0.f, 0.f, .5f);
		glVertex3f(0, 0, 0.f);
		glVertex3f(1024.0, 0, 0.f);
		glVertex3f(1024.0, 1024.0/(16.0/9.0), 0.f);
		glVertex3f(0, 1024.0/(16.0/9.0), 0.f);
	}
	glEnd();

	//HACK hardcoded cursor length
	glBegin(GL_LINES);
	{
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glVertex3f(positionOfCursor+2.f, 1, 0);
		glVertex3f(positionOfCursor+2.f, 20.f, 0);
	}
	glEnd();

	m_log.m_fontRenderer.drawString(Vector3f(1,1,0), commandAsString);
	m_log.render();
	glPopMatrix();
}


void Console::insertCharacterIntoCommand(unsigned char asKey)
{
	m_command.insert(m_command.begin()+m_currentTextOffset, asKey);
	m_currentTextOffset++;
}

bool Console::executeCommand()
{
	//HACK this wasn't working right for some reason
	FontRenderer::s_fallbackFont = &(m_log.m_fontRenderer.m_fontToUse);
	ConsoleLog::s_logText = (m_log.m_logText);

	//convert m_command into a string
	std::string commandAsString = std::string();
	for(unsigned int ii = 0; ii < m_command.size(); ii++)
	{
		commandAsString.append(1, m_command[ii]);
	}

	m_log.appendLine(commandAsString);
	//TODO consider moving this into command parser or renaming command parser
	unsigned int ii;
	bool spaceNotFound;
	for(ii = 0, spaceNotFound = true; ii < commandAsString.size() && spaceNotFound; ii++)
	{
		spaceNotFound = commandAsString.at(ii) != ' ';
	}
	if(!spaceNotFound)
	{
		std::string commandName = commandAsString.substr(0, ii-1);
		std::string arguments = commandAsString.substr(ii);
		CommandParser::ExecuteCommand(commandName, arguments);
	}
	else
	{
		CommandParser::ExecuteCommand(commandAsString, "");
	}

	m_currentTextOffset = 0;
	m_command.clear();
	return false;
}

