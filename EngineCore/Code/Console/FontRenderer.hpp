#pragma once
#ifndef include_FONTRENDERER
#define include_FONTRENDERER

#include "FontHandler.hpp"
#include "..\Primitives\Vector3f.hpp"
#include "..\Rendering\Material.hpp"

class FontRenderer
{
public:
	FontRenderer();

	static FontHandler* s_fallbackFont;
	FontHandler m_fontToUse;
	Material m_material;

	//TODO get the font to have an up vector as well as forward vector
	void drawString(Vector3f startBottomLeft, std::string contentsToDraw);
	static float CalcTextWidth(std::string contentsToMeasure, float heightOfText);
};


#endif