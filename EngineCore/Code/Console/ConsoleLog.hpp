#pragma once
#ifndef include_CONSOLELOG
#define include_CONSOLELOG


#include <string>

const int SIZE_OF_LOG = 255;
const int ROWS_TO_DISPLAY_ON_SCREEN = 20;
const float HEIGHT_OF_LOG = 500.f;

#include "FontRenderer.hpp"

class ConsoleLog
{
public:
	ConsoleLog();

	std::string m_logText[SIZE_OF_LOG];
	static int s_currentOffset;
	static std::string* s_logText;
	FontRenderer m_fontRenderer;

	void appendLine(std::string lineToBeAppended);
	void render();
	static void GlobalAppendLine(std::string lineToBeAppended);
};



#endif