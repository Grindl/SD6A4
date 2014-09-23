#pragma once
#ifndef include_WIN32_IOHANDLER
#define include_WIN32_IOHANDLER

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
typedef HWND WindowHandle;
#endif

class IOHandler
{
public:
	IOHandler();
	//TODO consider making the IOHandler a static global object
	bool KeyDownEvent(unsigned char asKey);
	bool KeyUpEvent(unsigned char asKey);

	bool MouseMoveEvent();
	bool MouseClickEvent();
	bool MouseButtonPressEvent();
	bool MouseButtonReleaseEvent();

	bool m_keyIsDown[256];
	bool m_mouseButtonIsDown[3];
	enum MouseButton {LEFT, RIGHT, MIDDLE};
	bool m_hasFocus;
	WindowHandle m_clientWindow;
};

#endif