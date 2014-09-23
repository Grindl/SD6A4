// Used with permission from Squirrel Eiserloh

//-----------------------------------------------------------------------------------------------
// ErrorWarningAssert.cpp

#define WIN32_LEAN_AND_MEAN
#define PLATFORM_WINDOWS //HACK for the sake of argument
#include <Windows.h>
//-----------------------------------------------------------------------------------------------
#include "ErrorWarningAssert.hpp"
#include <stdarg.h>
#include <iostream>

#include "Memory Manager/MemoryManager.hpp"


std::string g_appName = "HACK"; //HACK for the sake of it working

//-----------------------------------------------------------------------------------------------
bool IsDebuggerAvailable()
{
#if defined( PLATFORM_WINDOWS )
	typedef BOOL (CALLBACK IsDebugFuncType)();

	// Get a handle to KERNEL32.DLL
	HINSTANCE hInstanceKernel32 = GetModuleHandle( TEXT( "KERNEL32" ) );
	if( !hInstanceKernel32 )
		return false;

	// Get a handle to the IsDebuggerPresent() function in KERNEL32.DLL
	IsDebugFuncType* isDebuggerPresentFunc = (IsDebugFuncType*) GetProcAddress( hInstanceKernel32, "IsDebuggerPresent" );
	if( !isDebuggerPresentFunc )
		return false;

	// Now CALL that function and return its result
	BOOL isDebuggerAvailable = isDebuggerPresentFunc();
	return( isDebuggerAvailable == TRUE );
#else
	return false;
#endif
}


//-----------------------------------------------------------------------------------------------
void DebuggerPrintf( const char* messageFormat, ... )
{
	const int MESSAGE_MAX_LENGTH = 2048;
	char messageLiteral[ MESSAGE_MAX_LENGTH ];
	va_list variableArgumentList;
	va_start( variableArgumentList, messageFormat );
	vsnprintf_s( messageLiteral, MESSAGE_MAX_LENGTH, _TRUNCATE, messageFormat, variableArgumentList );
	va_end( variableArgumentList );
	messageLiteral[ MESSAGE_MAX_LENGTH - 1 ] = '\0'; // In case vsnprintf overran (doesn't auto-terminate)

#if defined( PLATFORM_WINDOWS )
	if( IsDebuggerAvailable() )
	{
		OutputDebugStringA( messageLiteral );
	}
#endif

	std::cout << messageLiteral;
}


//-----------------------------------------------------------------------------------------------
// Converts a Gypsy SeverityLevel to a Windows MessageBox icon type (MB_etc)
//
#if defined( PLATFORM_WINDOWS )
UINT GetWindowsMessageBoxIconFlagForSeverityLevel( SeverityLevel severity )
{
	switch( severity )
	{
		case SEVERITY_INFORMATION:		return MB_ICONASTERISK;		// blue circle with 'i' in Windows 7
		case SEVERITY_QUESTION:			return MB_ICONQUESTION;		// blue circle with '?' in Windows 7
		case SEVERITY_WARNING:			return MB_ICONEXCLAMATION;	// yellow triangle with '!' in Windows 7
		case SEVERITY_FATAL:			return MB_ICONHAND;			// red circle with 'x' in Windows 7
		default:						return MB_ICONEXCLAMATION;
	}
}
#endif


//-----------------------------------------------------------------------------------------------
void SystemDialogue_Okay( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	#if defined( PLATFORM_WINDOWS )
	{
		ShowCursor( TRUE );
		UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
		MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_OK | dialogueIconTypeFlag | MB_TOPMOST );
		ShowCursor( FALSE );
	}
	#endif
}


//-----------------------------------------------------------------------------------------------
// Returns true if OKAY was chosen, false if CANCEL was chosen.
//
bool SystemDialogue_OkayCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	bool isAnswerOkay = true;

	#if defined( PLATFORM_WINDOWS )
	{
		ShowCursor( TRUE );
		UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
		int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_OKCANCEL | dialogueIconTypeFlag | MB_TOPMOST );
		isAnswerOkay = (buttonClicked == IDOK);
		ShowCursor( FALSE );
	}
	#endif

	return isAnswerOkay;
}


//-----------------------------------------------------------------------------------------------
// Returns true if YES was chosen, false if NO was chosen.
//
bool SystemDialogue_YesNo( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	bool isAnswerYes = true;

	#if defined( PLATFORM_WINDOWS )
	{
		ShowCursor( TRUE );
		UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
		int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_YESNO | dialogueIconTypeFlag | MB_TOPMOST );
		isAnswerYes = (buttonClicked == IDYES);
		ShowCursor( FALSE );
	}
	#endif

	return isAnswerYes;
}


//-----------------------------------------------------------------------------------------------
// Returns 1 if YES was chosen, 0 if NO was chosen, -1 if CANCEL was chosen.
//
int SystemDialogue_YesNoCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity )
{
	int answerCode = 1;

	#if defined( PLATFORM_WINDOWS )
	{
		ShowCursor( TRUE );
		UINT dialogueIconTypeFlag = GetWindowsMessageBoxIconFlagForSeverityLevel( severity );
		int buttonClicked = MessageBoxA( NULL, messageText.c_str(), messageTitle.c_str(), MB_YESNOCANCEL | dialogueIconTypeFlag | MB_TOPMOST );
		answerCode = (buttonClicked == IDYES ? 1 : (buttonClicked == IDNO ? 0 : -1) );
		ShowCursor( FALSE );
	}
	#endif

	return answerCode;
}


//-----------------------------------------------------------------------------------------------
__declspec( noreturn ) void FatalError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText )
{
	std::string fullMessageTitle = g_appName + " :: Error";
	std::string fullMessageText = errorMessage;
	fullMessageText += "\n\nThe application will now close.\n";
	bool isDebuggerPresent = (IsDebuggerPresent() == TRUE);

	if( conditionText )
	{
		fullMessageText += "\n---------- Debugging Details Follow ----------\n";
		//fullMessageText += Stringf( "\nThis error was caused by a run-time condition check from line %d of:\n%s\n\nThe condition asserted which failed was:\n  \"%s\"\n", cppLineNum, cppFileName, conditionText );
	}

	DebuggerPrintf( "%s(%d): %s", cppFileName, cppLineNum, fullMessageText.c_str() ); // Use this specific format so Visual Studio users can double-click to jump to file-and-line of error

	if( isDebuggerPresent )
	{
		fullMessageText += "\nDEBUGGER DETECTED!\nWould you like to break and debug?\n  (No to quit)\n";
		bool isAnswerYes = SystemDialogue_YesNo( fullMessageTitle, fullMessageText, SEVERITY_FATAL );
		ShowCursor( TRUE );
		if( isAnswerYes )
		{
			__debugbreak();
		}
	}
	else
	{
		SystemDialogue_Okay( fullMessageTitle, fullMessageText, SEVERITY_FATAL );
		ShowCursor( TRUE );
	}

	exit( -1 );
}


//-----------------------------------------------------------------------------------------------
void RecoverableError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText )
{
	std::string fullMessageTitle = g_appName + " :: Warning";
	std::string fullMessageText = errorMessage;
	bool isDebuggerPresent = (IsDebuggerPresent() == TRUE);

	if( isDebuggerPresent )
	{
		fullMessageText += "\n\nDEBUGGER DETECTED!\nWould you like to continue running?\n  (Cancel to debug, No to quit)\n";
	}
	else
	{
		fullMessageText += "\n\nWould you like to continue running?\n  (No to quit)\n";
	}

	if( conditionText )
	{
		fullMessageText += "\n---------- Debugging Details Follow ----------\n";
		//fullMessageText += Stringf( "\nThis error was caused by a run-time condition check from line %d of:\n%s\n\nThe condition asserted which failed was:\n  \"%s\"\n", cppLineNum, cppFileName, conditionText );
	}

	DebuggerPrintf( "%s(%d): %s", cppFileName, cppLineNum, fullMessageText.c_str() ); // Use this specific format so Visual Studio users can double-click to jump to file-and-line of error

	if( isDebuggerPresent )
	{
		int answerCode = SystemDialogue_YesNoCancel( fullMessageTitle, fullMessageText, SEVERITY_WARNING );
		ShowCursor( TRUE );
		if( answerCode == 0 ) // "NO"
		{
			exit( -1 );
		}
		else if( answerCode == -1 ) // "CANCEL"
		{
			__debugbreak();
		}
	}
	else
	{
		bool isAnswerYes = SystemDialogue_YesNo( fullMessageTitle, fullMessageText, SEVERITY_WARNING );
		ShowCursor( TRUE );
		if( !isAnswerYes )
		{
			exit( -1 );
		}
	}
}

