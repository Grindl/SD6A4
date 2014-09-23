#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "..\Primitives\VertexData.hpp"
#include "..\Rendering\OpenGLFunctions.hpp"
#include "..\Debug Graphics\DebugAABB3.hpp"

#include "Memory Manager/MemoryManager.hpp"

DebugAABB3::DebugAABB3()
{
	m_origin = Vector3f();
	m_firstColor = Color4f();
	m_farCorner = Vector3f();
	m_edgeColor = Color4f();
	m_timeToLiveSeconds = 0.f;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_hasTexture = false;
	m_material = Material();
}

DebugAABB3::DebugAABB3(Vector3f origin, Color4f sideColor, Vector3f farCorner, Color4f edgeColor, float displayForSeconds, bool depthTest)
{
	m_origin = origin;
	m_firstColor = sideColor;
	m_farCorner = farCorner;
	m_edgeColor = edgeColor;
	m_timeToLiveSeconds = displayForSeconds;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_depthTest = depthTest;
	m_hasTexture = false;
	calculateVerticies();
	genVBO();
	m_material = Material();
}

void DebugAABB3::render()
{

	if(m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}


	//m_material.prepareOpenGLForMaterial();
	renderVBO();
	//renderPrimitive();
}

void DebugAABB3::calculateVerticies()
{
	//bottom left front
	verteces[0][0] = m_origin.x;
	verteces[0][1] = m_origin.y;
	verteces[0][2] = m_origin.z;

	//top left front
	verteces[1][0] = m_origin.x;
	verteces[1][1] = m_origin.y;
	verteces[1][2] = m_farCorner.z;

	//bottom left back
	verteces[2][0] = m_origin.x;
	verteces[2][1] = m_farCorner.y;
	verteces[2][2] = m_origin.z;

	//top left back
	verteces[3][0] = m_origin.x;
	verteces[3][1] = m_farCorner.y;
	verteces[3][2] = m_farCorner.z;

	//bottom right front
	verteces[4][0] = m_farCorner.x;
	verteces[4][1] = m_origin.y;
	verteces[4][2] = m_origin.z;

	//top right front
	verteces[5][0] = m_farCorner.x;
	verteces[5][1] = m_origin.y;
	verteces[5][2] = m_farCorner.z;

	//bottom right back
	verteces[6][0] = m_farCorner.x;
	verteces[6][1] = m_farCorner.y;
	verteces[6][2] = m_origin.z;

	//top right back
	verteces[7][0] = m_farCorner.x;
	verteces[7][1] = m_farCorner.y;
	verteces[7][2] = m_farCorner.z;
}

void DebugAABB3::genVBO()
{
	int SIZEOFVBO = 24;
	VertexData* m_VBO = new VertexData[SIZEOFVBO];
	m_VBOOffset = 0;
	float TEXTURE_CATALOG_DIVISIONS = 1.f;
	float x = 0;
	float y = 0;


	float light = 1.f;

	{
		//Left

		//010
		VertexData vert1 = {m_origin.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			0.f, -1.f, 0.f, 0.f, 0.f, -1.f, -1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//000
		VertexData vert2 = {m_origin.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			0.f, -1.f, 0.f, 0.f, 0.f, -1.f, -1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//001
		VertexData vert3 = {m_origin.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			0.f, -1.f, 0.f, 0.f, 0.f, -1.f, -1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//011
		VertexData vert4 = {m_origin.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y,
			0.f, -1.f, 0.f, 0.f, 0.f, -1.f, -1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}

	{
		//Front

		//000
		VertexData vert1 = {m_origin.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, -1.f, 0.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//100
		VertexData vert2 = {m_farCorner.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, -1.f, 0.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//101
		VertexData vert3 = {m_farCorner.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, -1.f, 0.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//001
		VertexData vert4 = {m_origin.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y,
			1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, -1.f, 0.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}

	{
		//Bottom

		//010
		VertexData vert1 = {m_origin.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//110
		VertexData vert2 = {m_farCorner.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//100
		VertexData vert3 = {m_farCorner.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//000
		VertexData vert4 = {m_origin.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y,
			1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}

	{
		//Right

		//100
		VertexData vert1 = {m_farCorner.x, m_origin.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//110
		VertexData vert2 = {m_farCorner.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//111
		VertexData vert3 = {m_farCorner.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//101
		VertexData vert4 = {m_farCorner.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y,
			0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f, 0.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}

	{
		//Far

		//110
		VertexData vert1 = {m_farCorner.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//010
		VertexData vert2 = {m_origin.x, m_farCorner.y, m_origin.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//011
		VertexData vert3 = {m_origin.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//111
		VertexData vert4 = {m_farCorner.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x,  y,
			-1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}


	{
		//Top

		//001
		VertexData vert1 = {m_origin.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		m_VBO[m_VBOOffset] = vert1;
		m_VBOOffset++;
		//101
		VertexData vert2 = {m_farCorner.x, m_origin.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f, 
			x+TEXTURE_CATALOG_DIVISIONS,  y+TEXTURE_CATALOG_DIVISIONS,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		m_VBO[m_VBOOffset] = vert2;
		m_VBOOffset++;
		//111
		VertexData vert3 = {m_farCorner.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x+TEXTURE_CATALOG_DIVISIONS,  y,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		m_VBO[m_VBOOffset] = vert3;
		m_VBOOffset++;
		//011
		VertexData vert4 = {m_origin.x, m_farCorner.y, m_farCorner.z, 
			m_firstColor.red*light, m_firstColor.green*light, m_firstColor.blue*light, 1.f,
			x,  y,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		m_VBO[m_VBOOffset] = vert4;
		m_VBOOffset++;
	}


	glGenBuffers(1, &m_OGLBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*m_VBOOffset, m_VBO, GL_STATIC_DRAW);
	delete m_VBO;
}

void DebugAABB3::renderPrimitive()
{
	m_material.prepareOpenGLForMaterial();
	glBegin(GL_QUADS);
	{
		//far 2367
		glColor4f(m_firstColor.red, m_firstColor.green, m_firstColor.blue, m_firstColor.alphaValue);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);


		//top 1357
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);

		//bottom 0246
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);

		//left 0123
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);


		//right 4567
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);


		//front 0145
		glTexCoord2f(0.f, 1.f);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);

	}
	glEnd();

	//HACK hardcoded line size
	glLineWidth(2.f);
	glBegin(GL_LINES);
	{
		//far 2367
		glColor4f(m_edgeColor.red, m_edgeColor.green, m_edgeColor.blue, m_edgeColor.alphaValue);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);


		//top 1357
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);

		//bottom 0246
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);

		//left 0123
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[3][0], verteces[3][1], verteces[3][2]);
		glVertex3f(verteces[2][0], verteces[2][1], verteces[2][2]);


		//right 4567
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glVertex3f(verteces[6][0], verteces[6][1], verteces[6][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[7][0], verteces[7][1], verteces[7][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);


		//front 0145
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glVertex3f(verteces[4][0], verteces[4][1], verteces[4][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[5][0], verteces[5][1], verteces[5][2]);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glVertex3f(verteces[1][0], verteces[1][1], verteces[1][2]);
		glVertex3f(verteces[0][0], verteces[0][1], verteces[0][2]);

	}
	glEnd();
}

void DebugAABB3::renderVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);

	//Note to self: this was moved from render() because it needs to be after bind buffer, but render is unsure if a VBO is being used
	m_material.prepareOpenGLForMaterial();

	glDrawArrays(GL_QUADS, 0, m_VBOOffset);
}