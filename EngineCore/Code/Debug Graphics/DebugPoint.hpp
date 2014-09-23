#pragma once
#ifndef include_DEBUGPOINT
#define include_DEBUGPOINT

#include "DebugElement.hpp"

class DebugPoint : public DebugElement
{
public:
	DebugPoint();
	DebugPoint(Vector3f source, Color4f firstColor, float displayForSeconds, bool depthTest);	

	int m_VBOOffset;
	unsigned int m_OGLBuffer;
	float m_pointSize;

	virtual void render();
	void genVBO();
	void VBORender();
	void fixedFunctionRender();
};


#endif