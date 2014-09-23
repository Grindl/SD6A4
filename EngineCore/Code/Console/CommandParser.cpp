#include "CommandParser.hpp"

#include "Memory Manager/MemoryManager.hpp"

std::map<std::string, funcPointer> CommandParser::s_functionMap;

//----------------------------------------------------------------------------------------
CommandParser::CommandParser()
{
	CommandParser::s_functionMap = std::map<std::string, funcPointer>();
}

//----------------------------------------------------------------------------------------
void CommandParser::RegisterCommand(std::string commandName, funcPointer functionToExecute)
{
	CommandParser::s_functionMap[commandName] = functionToExecute;
}

//----------------------------------------------------------------------------------------
bool CommandParser::ExecuteCommand(std::string commandName, std::string arguments)
{
	//TODO IMMEDIATE test this
	bool result = false;
	if(CommandParser::s_functionMap.find(commandName) != CommandParser::s_functionMap.end())
	{
		result = CommandParser::s_functionMap[commandName](arguments);
	}
	else
	{
		//TODO spit back an error
	}
	return result;
}