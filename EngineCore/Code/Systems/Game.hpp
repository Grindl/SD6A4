#pragma once
#ifndef include_GAME
#define include_GAME

#include "IOHandler.hpp"

class Game
{
public:
	IOHandler m_IOHandler;


	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual bool keyUpEvent(unsigned char asKey) {return m_IOHandler.KeyUpEvent(asKey);}
	virtual bool keyDownEvent(unsigned char asKey){return m_IOHandler.KeyDownEvent(asKey);}
	virtual bool characterEvent(unsigned char asKey, unsigned char scanCode)=0;
	virtual bool typingEvent(unsigned char asKey)=0;
	virtual bool mouseEvent(unsigned int eventType)=0;
};

#endif