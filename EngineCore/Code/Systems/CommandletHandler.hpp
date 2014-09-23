#pragma once
#ifndef include_COMMANDLETHANDLER
#define include_COMMANDLETHANDLER

#include <string>
#include <map>
#include <vector>

/*
1.	Command-line arguments and commandlets (30 points)
a.	(5 points) Parse your program’s command line arguments on startup (e.g. the 3rd argument for standard WinMain entry function).
b.	(20 points) Arguments should be parsed according to the following rules:
	i.	(3 points) Each argument is assumed to be whitespace delimited, and has leading & trailing whitespace-trimmed;
	ii.	(3 points) Arguments beginning with a ‘-‘ (hypen), such as “-generateFiles”, should be assumed to be commands;
	iii.	(3 points) Non-hyphen arguments following commands should be considered arguments for those commands (e.g. “-generateFiles 20 75”);
	iv.	(3 points) Anything in “quotation marks” should be considered a pure text literal (without the quotes) and should be treated as a single argument 
		(preserving whitespace within the quotes);
	v.	(3 points) A list of commands and the arguments for each command (e.g. a std::vector of std::vectors of std::strings) should be assembled;
	vi.	(5 points) A standalone function should be called to process these commands as early as possible (before window creation, etc.), with game code 
		(if applicable) getting first access to the command list (and being able to modify it) before the engine does.  This function should provide a return 
		value to indicate whether the normal startup sequence should continue or the program should exit.
c.	(5 points) Create at last one commandlet, “-generateFiles <fileCount> <KBPerFile>” which will, instead of running your program, generate X files of Y 
	kilobytes each of random bytes (and then exit the program).
	i.	for example:   MyApplication.exe -generateFiles 20 75   would generate 20 files of 75 KB each in size (named, say, generated_75kb_file_001.dat through 
		generated_75kb_file_020.dat) on disk, somewhere within your Data folder.


*/

namespace CommandletHandler
{
	typedef bool (*commandletFuncPointer)(std::vector<std::string> arguments);
	static std::map<std::string, commandletFuncPointer> g_commandletMap;


	void ProcessStartupArguments(const std::string& rawStartupArguments);
	void RegisterCommandlet(const std::string& commandletName, commandletFuncPointer functionToExecute);
	bool ExecuteCommandlet(const std::string& commandletName, const std::vector<std::string>& arguments);


};


#endif