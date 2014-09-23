#pragma once
#ifndef include_GLYPH
#define include_GLYPH


#include <string>

#include "..\Primitives\Vector2f.hpp"

class Glyph
{
public:
	Glyph();

	std::string m_fontName;
	std::string m_textValue;
	int m_textureSheetID;
	Vector2f m_bottomLeftTextureCoord;
	float m_height;
	float m_widthInTexture;
	float m_widthRelative;
	float m_leadingSpaceRelative;
	float m_trailingSpaceRelative;

};


#endif