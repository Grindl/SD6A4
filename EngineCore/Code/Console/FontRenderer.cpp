#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>

#include <string>

#include "..\Rendering\Texture.hpp"
#include "..\Debug Graphics\DebugLine.hpp"
#include "..\Rendering\OpenGLFunctions.hpp"
#include "FontRenderer.hpp"
#include "..\Primitives\VertexData.hpp"

#include "Memory Manager/MemoryManager.hpp"

FontHandler* FontRenderer::s_fallbackFont = 0;

FontRenderer::FontRenderer()
{
	m_fontToUse = FontHandler();
	s_fallbackFont = &m_fontToUse;
	m_material = Material();
	m_material.m_useDiffuse = true;
	m_material.m_useShaderProgram = true;
}

void FontRenderer::drawString(Vector3f startBottomLeft, std::string contentsToDraw)
{
	Vector3f cursorLocation = startBottomLeft;
	Vector3f normalizedCursorDirection = Vector3f(1.f, 0.f, 0.f);
	Vector3f normalizedUpDirection = Vector3f(0.f, 1.f, 0.f);
	//HACK
	float fontHeight = 20.f;
	Vector3f cursorUp = normalizedUpDirection * fontHeight;
	int previousTextureID = m_fontToUse.m_alphabet[contentsToDraw.substr(0, 1)].m_textureSheetID;
	m_material.m_diffuseID = previousTextureID;
	int VBOMaxSize = contentsToDraw.size() * 4;
	VertexData* VBOForString = new VertexData[VBOMaxSize];
	int currentVBOOffset = 0;

	for(unsigned int ii = 0; ii < contentsToDraw.size(); ii++)
	{
		Glyph nextGlyph = m_fontToUse.m_alphabet[contentsToDraw.substr(ii, 1)];
		cursorLocation = cursorLocation + (normalizedCursorDirection * (nextGlyph.m_leadingSpaceRelative*fontHeight));
		Vector3f glyphEndPoint = cursorLocation + (normalizedCursorDirection * (nextGlyph.m_widthRelative*fontHeight));

		if(previousTextureID != nextGlyph.m_textureSheetID)
		{
			//TODO stop this VBO, render it, and make a new one
			bool TOOBIGTOFAIL = true;
		}
		previousTextureID = nextGlyph.m_textureSheetID;

		//010
		VertexData vert1 = {cursorLocation.x, cursorLocation.y, cursorLocation.z,
			1.f, 1.f, 1.f, 1.f, 
			nextGlyph.m_bottomLeftTextureCoord.x, nextGlyph.m_bottomLeftTextureCoord.y+nextGlyph.m_height,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		VBOForString[currentVBOOffset] = vert1;
		currentVBOOffset++;
		//000
		VertexData vert2 = {cursorLocation.x+cursorUp.x, glyphEndPoint.y+cursorUp.y, cursorLocation.z+cursorUp.z, 
			1.f, 1.f, 1.f, 1.f, 
			nextGlyph.m_bottomLeftTextureCoord.x, nextGlyph.m_bottomLeftTextureCoord.y,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		VBOForString[currentVBOOffset] = vert2;
		currentVBOOffset++;
		//001
		VertexData vert3 = {glyphEndPoint.x+cursorUp.x, glyphEndPoint.y+cursorUp.y, glyphEndPoint.z+cursorUp.z,
			1.f, 1.f, 1.f, 1.f, 
			nextGlyph.m_bottomLeftTextureCoord.x+nextGlyph.m_widthInTexture, nextGlyph.m_bottomLeftTextureCoord.y,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		VBOForString[currentVBOOffset] = vert3;
		currentVBOOffset++;
		//011
		VertexData vert4 = {glyphEndPoint.x, cursorLocation.y, glyphEndPoint.z, 
			1.f, 1.f, 1.f, 1.f, 
			nextGlyph.m_bottomLeftTextureCoord.x+nextGlyph.m_widthInTexture, nextGlyph.m_bottomLeftTextureCoord.y+nextGlyph.m_height,
			1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f};
		VBOForString[currentVBOOffset] = vert4;
		currentVBOOffset++;

		/*glBegin(GL_QUADS);
		{
			glColor4f(1.f, .1f, .1f, 1.f);
			glDisable(GL_TEXTURE_2D);
			//glTexCoord2f(nextGlyph.m_bottomLeftTextureCoord.x, nextGlyph.m_bottomLeftTextureCoord.y+nextGlyph.m_height);
			glVertex3f(cursorLocation.x, cursorLocation.y, cursorLocation.z);

			//glTexCoord2f(nextGlyph.m_bottomLeftTextureCoord.x, nextGlyph.m_bottomLeftTextureCoord.y);
			glVertex3f(cursorLocation.x+cursorUp.x, glyphEndPoint.y+cursorUp.y, cursorLocation.z+cursorUp.z);

			//glTexCoord2f(nextGlyph.m_bottomLeftTextureCoord.x+nextGlyph.m_widthInTexture, nextGlyph.m_bottomLeftTextureCoord.y);
			glVertex3f(glyphEndPoint.x+cursorUp.x, glyphEndPoint.y+cursorUp.y, glyphEndPoint.z+cursorUp.z);

			//glTexCoord2f(nextGlyph.m_bottomLeftTextureCoord.x+nextGlyph.m_widthInTexture, nextGlyph.m_bottomLeftTextureCoord.y+nextGlyph.m_height);
			glVertex3f(glyphEndPoint.x, cursorLocation.y, glyphEndPoint.z);
		}
		glEnd();*/

		cursorLocation = glyphEndPoint + (normalizedCursorDirection * (nextGlyph.m_trailingSpaceRelative * fontHeight));
	}
	unsigned int VBOID;
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*currentVBOOffset, VBOForString, GL_STATIC_DRAW);
	delete VBOForString;
	m_material.prepareOpenGLForMaterial();
	glDrawArrays(GL_QUADS, 0, currentVBOOffset);
	//TODO add this to anywhere that I'm removing a VBO
	glDeleteBuffers(1, &VBOID);
}

float FontRenderer::CalcTextWidth(std::string contentsToMeasure, float heightOfText)
{
	float lengthOfLine = 0.f;
	Vector3f cursorLocation = Vector3f(0,0,0);
	Vector3f normalizedCursorDirection = Vector3f(1.f, 0.f, 0.f);

	//TODO test to make sure the static fallback font works
	for(unsigned int ii = 0; ii < contentsToMeasure.size(); ii++)
	{	
		Glyph nextGlyph = s_fallbackFont->m_alphabet[contentsToMeasure.substr(ii, 1)];
		cursorLocation = cursorLocation + (normalizedCursorDirection * (nextGlyph.m_leadingSpaceRelative*heightOfText));
		Vector3f glyphEndPoint = cursorLocation + (normalizedCursorDirection * (nextGlyph.m_widthRelative*heightOfText));
		cursorLocation = glyphEndPoint + (normalizedCursorDirection * (nextGlyph.m_trailingSpaceRelative * heightOfText));
	}
	lengthOfLine = cursorLocation.magnitude();
	return lengthOfLine;

}