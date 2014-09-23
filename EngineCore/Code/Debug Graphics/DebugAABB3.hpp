#pragma once
#ifndef include_DEBUGAABB3
#define include_DEBUGAABB3

#include "DebugElement.hpp"

class DebugAABB3 : public DebugElement
{
public:
	DebugAABB3();
	DebugAABB3(Vector3f origin, Color4f sideColor, Vector3f farCorner, Color4f edgeColor, float displayForSeconds, bool depthTest);

	Vector3f m_farCorner;
	Color4f m_edgeColor;
	int m_VBOOffset;
	unsigned int m_OGLBuffer;

	virtual void render();
private:
	float verteces[8][3];
	void calculateVerticies();
	void genVBO();
	void renderPrimitive();
	void renderVBO();
};


#endif