#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "..\Rendering\OpenGLFunctions.hpp"
#include "DebugElement.hpp"

#include "Memory Manager/MemoryManager.hpp"

DebugElement::DebugElement()
{
	m_timeToLiveSeconds = 0.f;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_hasTexture = false;
}

DebugElement::DebugElement(Vector3f source, Color4f firstColor, float displayForSeconds, bool depthTest)
	:m_origin(source)
	,m_firstColor(firstColor)
	,m_timeToLiveSeconds(displayForSeconds)
{
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_depthTest = depthTest;
	m_hasTexture = false;
}

void DebugElement::update(float deltaSeconds)
{
	if(m_killNextFrame)
	{
		m_shouldBeRemoved = true;
	}
	else
	{
		m_timeToLiveSeconds -= deltaSeconds;
		if(m_timeToLiveSeconds < 0.f)
		{
			m_killNextFrame = true;
		}
	}
	

}


void DebugElement::render()
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

	glBegin(GL_POINTS);
	{
		glColor4f(m_firstColor.red, m_firstColor.green, m_firstColor.blue, m_firstColor.alphaValue);
		glVertex3f(m_origin.x, m_origin.y, m_origin.z);
	}
	glEnd();
	//TODO: draw once with depthTest off, then again with depthTest on
}

bool DebugElement::shouldBeRemoved()
{
	return m_shouldBeRemoved;
}