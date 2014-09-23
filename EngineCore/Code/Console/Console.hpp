#pragma once
#ifndef include_CONSOLE
#define include_CONSOLE


#include <vector>

#include "ConsoleLog.hpp"


class Console
{
public:
	Console();

	ConsoleLog m_log;
	int m_currentTextOffset;
	std::vector<unsigned char> m_command;


	void render();
	void insertCharacterIntoCommand(unsigned char asKey);
	bool executeCommand();

};

#endif