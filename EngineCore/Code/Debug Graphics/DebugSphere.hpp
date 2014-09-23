#pragma once
#ifndef include_DEBUGSPHERE
#define include_DEBUGSPHERE

#include "DebugElement.hpp"

class DebugSphere : public DebugElement
{
public:
	DebugSphere();
	DebugSphere(Vector3f origin, float radius, Color4f sideColor, Color4f edgeColor, float displayForSeconds, bool depthTest);

	float m_radius;
	Color4f m_edgeColor;

	virtual void render();
};


#endif