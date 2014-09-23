#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "..\Rendering\OpenGLFunctions.hpp"
#include "DebugLine.hpp"

#include "Memory Manager/MemoryManager.hpp"

DebugLine::DebugLine()
	:m_destination()
	,m_secondColor()
{
	//TODO check to see if the other elements are initialized correctly with the implicit Super() calls
}

DebugLine::DebugLine(Vector3f origin, Color4f firstColor, Vector3f destination, Color4f secondColor, float displayForSeconds, bool depthTest)
	:m_destination(destination)
	,m_secondColor(secondColor)
{
	m_origin = origin;
	m_firstColor = firstColor;
	m_timeToLiveSeconds = displayForSeconds;
	m_depthTest = depthTest;
	m_hasTexture = false;
}

void DebugLine::render()
{
	int diffuseLocation = glGetUniformLocation(m_shaderID, "u_diffuseTexture");
	glUniform1i(diffuseLocation, 0);
	if(m_hasTexture)
	{	
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);		
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glDisable(GL_TEXTURE_2D);
	}
	int textureFlag = glGetUniformLocation(m_shaderID, "u_useTexture");
	glUniform1f(textureFlag, m_hasTexture);

	if(m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	glBegin(GL_LINES);
	{
		glColor4f(m_firstColor.red, m_firstColor.green, m_firstColor.blue, m_firstColor.alphaValue);
		glVertex3f(m_origin.x, m_origin.y, m_origin.z);

		glColor4f(m_secondColor.red, m_secondColor.green, m_secondColor.blue, m_secondColor.alphaValue);
		glVertex3f(m_destination.x, m_destination.y, m_destination.z);
	}
	glEnd();
}