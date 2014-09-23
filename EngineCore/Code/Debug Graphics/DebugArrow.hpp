#pragma once
#ifndef include_DEBUGARROW
#define include_DEBUGARROW

#include "DebugLine.hpp"

class DebugArrow : public DebugLine
{
public:
	DebugArrow();
	DebugArrow(Vector3f origin, Color4f firstColor, Vector3f destination, Color4f secondColor, float displayForSeconds, bool depthTest);

	virtual void render();
};


#endif