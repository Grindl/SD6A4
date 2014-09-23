#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "..\Primitives\VertexData.hpp"
#include "..\Rendering\OpenGLFunctions.hpp"
#include "..\Debug Graphics\DebugPoint.hpp"

#include "Memory Manager/MemoryManager.hpp"

DebugPoint::DebugPoint()
{
	m_pointSize = .3f;
	m_origin = Vector3f();
	m_firstColor = Color4f();
	m_timeToLiveSeconds = 0.f;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_hasTexture = false;
	m_material = Material();
}

DebugPoint::DebugPoint(Vector3f source, Color4f firstColor, float displayForSeconds, bool depthTest)
{
	m_pointSize = .3f;
	m_origin = source;
	m_firstColor = firstColor;
	m_timeToLiveSeconds = displayForSeconds;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_depthTest = depthTest;
	m_hasTexture = false;
	m_material = Material();
	genVBO();
	m_material.m_useVBO = true;
}

void DebugPoint::render()
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

	VBORender();
	//fixedFunctionRender();

	glPopMatrix();
}

void DebugPoint::genVBO()
{
	int SIZEOFVBO = 8;
	VertexData* m_VBO = new VertexData[SIZEOFVBO];
	m_VBOOffset = 0;
	float TEXTURE_CATALOG_DIVISIONS = 1.f;
	float x = 0;
	float y = 0;
	float light = 1.f;
	Vector3f pointOffset = Vector3f(m_pointSize, m_pointSize, m_pointSize);

	Vector3f bottomLeft = Vector3f(0,0,0) - pointOffset;
	Vector3f farCorner = Vector3f(0,0,0) + pointOffset;

	VertexData vert1 = {bottomLeft.x, bottomLeft.y, bottomLeft.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert1;
	m_VBOOffset++;
	VertexData vert2 = {farCorner.x, farCorner.y, farCorner.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert2;
	m_VBOOffset++;

	VertexData vert3 = {bottomLeft.x, bottomLeft.y, farCorner.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert3;
	m_VBOOffset++;
	VertexData vert4 = {farCorner.x, farCorner.y, bottomLeft.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert4;
	m_VBOOffset++;

	VertexData vert5 = {bottomLeft.x, farCorner.y, bottomLeft.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert5;
	m_VBOOffset++;
	VertexData vert6 = {farCorner.x, bottomLeft.y, farCorner.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert6;
	m_VBOOffset++;

	VertexData vert7 = {farCorner.x, bottomLeft.y, bottomLeft.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert7;
	m_VBOOffset++;
	VertexData vert8 = {bottomLeft.x, farCorner.y, farCorner.z, 
		m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
		x,  y+TEXTURE_CATALOG_DIVISIONS,
		1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
	m_VBO[m_VBOOffset] = vert8;
	m_VBOOffset++;

	glGenBuffers(1, &m_OGLBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*m_VBOOffset, m_VBO, GL_STATIC_DRAW);
	delete m_VBO;
}

void DebugPoint::VBORender()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);
	m_material.prepareOpenGLForMaterial();
	glDrawArrays(GL_LINES, 0, m_VBOOffset);
}

void DebugPoint::fixedFunctionRender()
{
	m_material.prepareOpenGLForMaterial();

	glBegin(GL_LINES);
	{
		glColor4f(m_firstColor.red, m_firstColor.green, m_firstColor.blue, m_firstColor.alphaValue);
		glVertex3f(+m_pointSize, +m_pointSize, +m_pointSize);
		glVertex3f(-m_pointSize, -m_pointSize, -m_pointSize);

		glVertex3f(+m_pointSize, +m_pointSize, -m_pointSize);
		glVertex3f(-m_pointSize, -m_pointSize, +m_pointSize);

		glVertex3f(+m_pointSize, -m_pointSize, +m_pointSize);
		glVertex3f(-m_pointSize, +m_pointSize, -m_pointSize);

		glVertex3f(-m_pointSize, +m_pointSize, +m_pointSize);
		glVertex3f(+m_pointSize, -m_pointSize, -m_pointSize);
	}
	glEnd();
}