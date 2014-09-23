#pragma once
#ifndef include_DEBUGLINE
#define include_DEBUGLINE

#include "DebugElement.hpp"

class DebugLine : public DebugElement
{
public:
	DebugLine();
	DebugLine(Vector3f origin, Color4f firstColor, Vector3f destination, Color4f secondColor, float displayForSeconds, bool depthTest);

	Vector3f m_destination;
	Color4f m_secondColor;

	virtual void render();
};



#endif