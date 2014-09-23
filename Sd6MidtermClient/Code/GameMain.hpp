#pragma once
#ifndef include_PANZERFAUST
#define include_PANZERFAUST


#include <vector>

#include "Systems\Game.hpp"
#include "Primitives\Element.hpp"
#include "Rendering\Renderer.hpp"
#include "Console\ConsoleLog.hpp"
#include "Console\Console.hpp"
#include "Camera.hpp"
#include "User.hpp"

class Player;

class Tag : public Game
{
public:
	Tag();

	std::vector<Element*> m_elements;
	std::vector<User*> m_users;
	Renderer m_renderer;
	float m_internalTime;
	bool m_isQuitting;
	bool m_displayConsole;
	Console m_console;
	Camera m_worldCamera;

	virtual void update(float deltaTime);
	virtual void render();
	virtual bool keyDownEvent(unsigned char asKey);
	virtual bool characterEvent(unsigned char asKey, unsigned char scanCode);
	virtual bool typingEvent(unsigned char asKey);
	virtual bool mouseEvent(unsigned int eventType);

	void mouseUpdate();
	void renderUI();
};



#endif 

