// Used with permission from Squirrel Eiserloh

//-----------------------------------------------------------------------------------------------
// ErrorWarningAssert.hpp
//
#pragma once
#ifndef included_ErrorWarningAssert
#define included_ErrorWarningAssert

//-----------------------------------------------------------------------------------------------

#include <string>

//-----------------------------------------------------------------------------------------------
enum SeverityLevel
{
	SEVERITY_INFORMATION,
	SEVERITY_QUESTION,
	SEVERITY_WARNING,
	SEVERITY_FATAL
};


//-----------------------------------------------------------------------------------------------
void DebuggerPrintf( const char* messageFormat, ... );
bool IsDebuggerAvailable();
void RecoverableError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
__declspec( noreturn ) void FatalError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
void SystemDialogue_Okay( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
bool SystemDialogue_OkayCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
bool SystemDialogue_YesNo( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );
int SystemDialogue_YesNoCancel( const std::string& messageTitle, const std::string& messageText, SeverityLevel severity );



//-----------------------------------------------------------------------------------------------
// Summary of macros
//
// #define FATAL_ERROR( errorMessageText )						// Show error dialogue, then shut down the app; "MUST not reach this point"
// #define FATAL_GUARANTEE( condition, errorMessageText )		// If condition is false, show error dialogue then shut down the app; "MUST be true"
// #define FATAL_ASSERTION( condition, errorMessageText )		// Same as FATAL_GUARANTEE, but removed if GYPSY_DISABLE_ASSERTS is #defined
// #define RECOVERABLE_ERROR( errorMessageText )				// Show error dialogue, then proceed; "SHOULD not reach this point"
// #define RECOVERABLE_GUARANTEE( condition, errorMessageText )	// If condition is false, show error dialogue then proceed; "SHOULD be true"
// #define RECOVERABLE_ASSERTION( condition, errorMessageText )	// Same as RECOVERABLE_GUARANTEE, but removed if GYPSY_DISABLE_ASSERTS is #defined
// 
// Most of these also have generic versions with one less parameter (no errorMessageText), but use of explicit errorMessageText is strongly encouraged.
//


/////////////////////////////////////////////////////////////////////////////////////////////////
// FATAL_ERROR
//
// Present in all builds.
// No condition; always triggers if reached.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
// Use this when reaching a certain line of code should never happen under any circumstances,
// and continued execution is dangerous or impossible.
//
#define FATAL_ERROR( errorMessageText )												\
{																					\
	FatalError( __FILE__, __LINE__, errorMessageText );								\
}

#define FATAL_ERROR_GENERIC															\
{																					\
	FatalError( __FILE__, __LINE__, "Fatal unspecified error" );					\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// FATAL_GUARANTEE
//
// Present in all builds.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
#define FATAL_GUARANTEE( condition, errorMessageText )								\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, errorMessageText, conditionText );			\
	}																				\
}

#define FATAL_GUARANTEE_GENERIC( condition )										\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, "Fatal unmet guarantee", conditionText );			\
	}																				\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// FATAL_ASSERTION
//
// Removed if GYPSY_DISABLE_ASSERTS is enabled, typically in a Final build configuration.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
#if defined( GYPSY_DISABLE_ASSERTS )
#define FATAL_ASSERTION( condition, errorMessageText ) { (void)( condition ); }
#else
#define FATAL_ASSERTION( condition, errorMessageText )								\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, errorMessageText, conditionText );			\
	}																				\
}
#endif

#if defined( GYPSY_DISABLE_ASSERTS )
#define FATAL_ASSERTION_GENERIC( condition ) { (void)( condition ); }
#else
#define FATAL_ASSERTION_GENERIC( condition )										\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, "Fatal unmet assertion", conditionText );	\
	}																				\
}
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////
// RECOVERABLE_ERROR
//
// Present in all builds.
// No condition; always triggers if reached.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#define RECOVERABLE_ERROR( errorMessageText )										\
{																					\
	RecoverableError( __FILE__, __LINE__, errorMessageText );						\
}

#define RECOVERABLE_ERROR_GENERIC													\
{																					\
	RecoverableError( __FILE__, __LINE__, "Unspecified error" );					\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// RECOVERABLE_GUARANTEE
//
// Present in all builds.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#define RECOVERABLE_GUARANTEE( condition, errorMessageText )						\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, errorMessageText, conditionText );	\
	}																				\
}

#define RECOVERABLE_GUARANTEE_GENERIC( condition )									\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, "Unmet guarantee", conditionText );	\
	}																				\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// RECOVERABLE_ASSERTION
//
// Removed if GYPSY_DISABLE_ASSERTS is enabled, typically in a Final build configuration.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#if defined( GYPSY_DISABLE_ASSERTS )
#define RECOVERABLE_ASSERTION( condition, errorMessageText ) { (void)( condition ); }
#else
#define RECOVERABLE_ASSERTION( condition, errorMessageText )						\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, errorMessageText, conditionText );	\
	}																				\
}
#endif

#if defined( GYPSY_DISABLE_ASSERTS )
#define RECOVERABLE_ASSERTION_GENERIC( condition ) { (void)( condition ); }
#else
#define RECOVERABLE_ASSERTION_GENERIC( condition )									\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, "Unmet assertion", conditionText );	\
	}																				\
}
#endif



#endif // included_ErrorWarningAssert
