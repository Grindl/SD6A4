#include "CommandletHandler.hpp"

#include "Memory Manager/MemoryManager.hpp"

//----------------------------------------------------------------------------------------
void CommandletHandler::ProcessStartupArguments(const std::string& rawStartupArguments)
{
	if (rawStartupArguments.size() == 0)
	{
		return;
	}

	std::vector<std::pair<unsigned int, unsigned int>> openAndClosedQuoteLocations;
	std::vector<unsigned int> commandletBeginLocations;
	std::vector<unsigned int> argumentSplitLocations;
	bool currentlyInQuotes = false;
	int currentOpenQuotePosition = -1;
	for (unsigned int argumentsIndex = 0; argumentsIndex < rawStartupArguments.size(); argumentsIndex++)
	{
		if (currentlyInQuotes)
		{
			if (rawStartupArguments[argumentsIndex] == '\"')
			{
				currentlyInQuotes = false;
				openAndClosedQuoteLocations.push_back(std::pair<unsigned int, unsigned int>(currentOpenQuotePosition, argumentsIndex));
			}
		}
		else
		{
			if (rawStartupArguments[argumentsIndex] == '\"')
			{
				currentlyInQuotes = true;
				currentOpenQuotePosition = argumentsIndex;
			}
			else if (rawStartupArguments[argumentsIndex] == '-')
			{
				commandletBeginLocations.push_back(argumentsIndex);
			}
			else if (rawStartupArguments[argumentsIndex] == ' ')
			{
				argumentSplitLocations.push_back(argumentsIndex);
			}
		}
	}
	commandletBeginLocations.push_back(rawStartupArguments.size()-1);
	int endOfCurrentCommandlet = -1;
	for (unsigned int commandletIndex = 1; commandletIndex < commandletBeginLocations.size(); commandletIndex++)
	{
		if (commandletIndex == commandletBeginLocations.size())
		{
			endOfCurrentCommandlet = rawStartupArguments.size()-1;
		}
		else
		{
			endOfCurrentCommandlet = commandletBeginLocations[commandletIndex];
		}
		unsigned int currentSplitIndex = 0;
		unsigned int currentSplitLoc = 0;
		while (currentSplitLoc <= commandletBeginLocations[commandletIndex-1] && currentSplitIndex < argumentSplitLocations.size())
		{
			currentSplitIndex++;
			currentSplitLoc = argumentSplitLocations[currentSplitIndex];
		}
		currentSplitIndex--;
		std::string commandletName = rawStartupArguments.substr(commandletBeginLocations[commandletIndex-1], argumentSplitLocations[currentSplitIndex]);
		std::vector<std::string> commandletArguments;
		argumentSplitLocations.push_back(commandletBeginLocations[commandletIndex]);
		while (currentSplitIndex <= commandletBeginLocations[commandletIndex] && currentSplitIndex < argumentSplitLocations.size()-1)
		{
			int startOfArgument = argumentSplitLocations[currentSplitIndex];
			int endOfArgument = argumentSplitLocations[currentSplitIndex+1];
			commandletArguments.push_back(rawStartupArguments.substr(startOfArgument, endOfArgument));
			currentSplitIndex++;
		}
		ExecuteCommandlet(commandletName, commandletArguments);
	}
}

//----------------------------------------------------------------------------------------
//potential problem: all commands need to be registered before the commandlets are called
void CommandletHandler::RegisterCommandlet(const std::string& commandletName, commandletFuncPointer functionToExecute)
{
		g_commandletMap[commandletName] = functionToExecute;
}

//----------------------------------------------------------------------------------------
bool CommandletHandler::ExecuteCommandlet(const std::string& commandletName, const std::vector<std::string>& arguments)
{
	//TODO test this
	if(g_commandletMap.find(commandletName) != g_commandletMap.end())
	{
		return (g_commandletMap[commandletName])(arguments);
	}
	else
	{
		//TODO assert
	}
	return false;
}