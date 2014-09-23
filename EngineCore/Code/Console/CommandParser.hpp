#pragma once
#ifndef include_COMMANDPARSER
#define include_COMMANDPARSER

#include <string>
#include <map>


typedef bool (*funcPointer)(std::string arguments);

class CommandParser
{
public:
	CommandParser();

	std::string m_commandToParse;
	static std::map<std::string, funcPointer> s_functionMap;

	static void RegisterCommand(std::string commandName, funcPointer functionToExecute);
	static bool ExecuteCommand(std::string commandName, std::string arguments);
};



#endif