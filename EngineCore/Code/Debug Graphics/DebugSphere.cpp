#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "..\Internal Dependencies\geometry.h"

#include "..\Rendering\OpenGLFunctions.hpp"
#include "DebugSphere.hpp"

#include "Memory Manager/MemoryManager.hpp"

DebugSphere::DebugSphere()
{
	m_material = Material();
}


DebugSphere::DebugSphere(Vector3f origin, float radius, Color4f sideColor, Color4f edgeColor, float displayForSeconds, bool depthTest)
{
	m_origin = origin;
	m_radius = radius;
	m_firstColor = sideColor;
	m_edgeColor = edgeColor;
	m_timeToLiveSeconds = displayForSeconds;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_depthTest = depthTest;
	m_hasTexture = false;
}

void DebugSphere::render()
{

	if(m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	glPushMatrix();
	glTranslatef(m_origin.x, m_origin.y, m_origin.z);

	m_material.prepareOpenGLForMaterial();

	glColor4f(m_firstColor.red, m_firstColor.green, m_firstColor.blue, m_firstColor.alphaValue);
	//renderSolidSphere(m_radius, 8, 8);

	glColor4f(m_edgeColor.red, m_edgeColor.green, m_edgeColor.blue, m_edgeColor.alphaValue);
	//renderWireSphere(m_radius, 8, 8);

	glPopMatrix();
}