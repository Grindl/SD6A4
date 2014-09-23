#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
#include <crtdbg.h>
#include <map>
#include <string>
#include <vector>

#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include "Data.hpp"
#include "Systems\Time Utility.hpp"
#include "Systems\IOHandler.hpp"
#include "Console\CommandParser.hpp"
#include "Systems\Game.hpp"
#include "GameMain.hpp"




Tag* g_theGame;

bool g_isQuitting = false;
HWND g_hWnd = nullptr;
HDC g_displayDeviceContext = nullptr;
HGLRC g_openGLRenderingContext = nullptr;
const char* APP_NAME = "SD6 MIDTERM - TAG";




LRESULT CALLBACK WindowsMessageHandlingProcedure( HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam )
{
	switch( wmMessageCode )
	{
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		g_isQuitting = true;
		return 0;
	case WM_KILLFOCUS:
		{
			g_theGame->m_IOHandler.m_hasFocus = false;
			break;
		}
	case WM_SETFOCUS:
		{
			g_theGame->m_IOHandler.m_hasFocus = true;
			break;
		}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		{
			g_theGame->mouseEvent(wmMessageCode);
			break;
		}

	case WM_KEYDOWN:
		{
			unsigned char asKey = (unsigned char) wParam;
			if( asKey == VK_ESCAPE )
			{
				g_isQuitting = true;
				return 0;
			}
			bool wasProcessed = g_theGame->keyDownEvent(asKey);
			if(wasProcessed)
			{
				return 0;
			}
			break;
		}
	case WM_KEYUP:
		{
			unsigned char asKey = (unsigned char) wParam;
			bool wasProcessed = g_theGame->keyUpEvent(asKey);
			if(wasProcessed)
			{
				return 0;
			}
			break;
		}
	case WM_CHAR:
		{
			/*unsigned char asKey = (unsigned char) wParam;
			unsigned int scanCodeMask = 0xFF0000;
			unsigned int maskedlParam = lParam & scanCodeMask;
			unsigned int shiftedlParam = maskedlParam>>16;
			unsigned char scanCode = (unsigned char) shiftedlParam;
			bool wasProcessed = g_theGame->characterEvent(asKey, scanCode);*/
			unsigned char asKey = (unsigned char) wParam;
			bool wasProcessed = g_theGame->typingEvent(asKey);
			if(wasProcessed)
			{
				return 0;
			}
			break;
		}
	}

	return DefWindowProc( windowHandle, wmMessageCode, wParam, lParam );
}

void CreateOpenGLWindow( HINSTANCE applicationInstanceHandle )
{

	WNDCLASSEX windowClassDescription;
	memset( &windowClassDescription, 0, sizeof( windowClassDescription ) );
	windowClassDescription.cbSize = sizeof( windowClassDescription );
	windowClassDescription.style = CS_OWNDC; // Redraw on move, request own Display Context
	windowClassDescription.lpfnWndProc = static_cast< WNDPROC >( WindowsMessageHandlingProcedure ); // Assign a win32 message-handling function
	windowClassDescription.hInstance = GetModuleHandle( NULL );
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT( "Simple Window Class" );
	RegisterClassEx( &windowClassDescription );

	const DWORD windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
	const DWORD windowStyleExFlags = WS_EX_APPWINDOW;

	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect( desktopWindowHandle, &desktopRect );

	RECT windowRect = { 50, 50, 50+SCREEN_WIDTH, 50+SCREEN_HEIGHT};
	AdjustWindowRectEx( &windowRect, windowStyleFlags, FALSE, windowStyleExFlags );

	WCHAR windowTitle[ SCREEN_WIDTH ];
	MultiByteToWideChar( GetACP(), 0, APP_NAME, -1, windowTitle, sizeof(windowTitle)/sizeof(windowTitle[0]) );
	g_hWnd = CreateWindowEx(
		windowStyleExFlags,
		windowClassDescription.lpszClassName,
		windowTitle,
		windowStyleFlags,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		applicationInstanceHandle,
		NULL );

	ShowWindow( g_hWnd, SW_SHOW );
	SetForegroundWindow( g_hWnd );
	SetFocus( g_hWnd );

	g_displayDeviceContext = GetDC( g_hWnd );

	HCURSOR cursor = LoadCursor( NULL, IDC_ARROW );
	SetCursor( cursor );

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset( &pixelFormatDescriptor, 0, sizeof( pixelFormatDescriptor ) );
	pixelFormatDescriptor.nSize			= sizeof( pixelFormatDescriptor );
	pixelFormatDescriptor.nVersion		= 1;
	pixelFormatDescriptor.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType	= PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits	= 24;
	pixelFormatDescriptor.cDepthBits	= 24;
	pixelFormatDescriptor.cAccumBits	= 0;
	pixelFormatDescriptor.cStencilBits	= 8;

	int pixelFormatCode = ChoosePixelFormat( g_displayDeviceContext, &pixelFormatDescriptor );
	SetPixelFormat( g_displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor );
	g_openGLRenderingContext = wglCreateContext( g_displayDeviceContext );
	wglMakeCurrent( g_displayDeviceContext, g_openGLRenderingContext );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glOrtho(1.f, WORLD_WIDTH-1, 1.f, WORLD_HEIGHT-1, 0.f, 1.f);
}

void RunMessagePump()
{
	MSG queuedMessage;
	for( ;; )
	{
		const BOOL wasMessagePresent = PeekMessage( &queuedMessage, NULL, 0, 0, PM_REMOVE );
		if( !wasMessagePresent )
		{
			break;
		}

		TranslateMessage( &queuedMessage );
		DispatchMessage( &queuedMessage );
	}
}



void update(float deltaSeconds)
{
	g_theGame->update(deltaSeconds);
	//HACK
	g_isQuitting = ((Tag*)g_theGame)->m_isQuitting || g_isQuitting;
}

void render()
{
	g_theGame->render();
}

float FrameDelay(double startTime)
{
	static double targetRefreshRate = 1/60.f;
	double targetTime = startTime + targetRefreshRate;
	double timeNow = startTime;
	//TODO: move me into the main loop
	while(timeNow < targetTime)
	{
		timeNow = getCurrentTimeSeconds();
	}
	return (float)(timeNow - startTime);

}

void runFrame()
{
	static float deltaSeconds = 0;
	double startTime =  getCurrentTimeSeconds();
	RunMessagePump();
	update(deltaSeconds);
	render();
	deltaSeconds = FrameDelay(startTime);
	SwapBuffers( g_displayDeviceContext );
}

bool quitGame(std::string unusedArgs)
{
	g_isQuitting = true;
	return true;
}

#define UNUSED(x) (void)x;

int WINAPI WinMain( HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR commandLineString, int )
{
	UNUSED( commandLineString ); 
	srand((unsigned int)time(NULL));
	initializeTimeUtility();

	//start the game
	CreateOpenGLWindow( applicationInstanceHandle );
	g_theGame = new Tag();
	CommandParser::RegisterCommand("quit", quitGame);
	g_theGame->m_IOHandler.m_clientWindow = g_hWnd;

	//ShowCursor(false); may be re-implemented once a custom cursor is in place
	while( !g_isQuitting )	
	{
		runFrame();
	}
	ShowCursor(true);
	delete g_theGame;

#if defined( _WIN32 ) && defined( _DEBUG )
	assert( _CrtCheckMemory() );
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}