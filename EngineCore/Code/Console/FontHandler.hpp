#pragma once
#ifndef include_FONTHANDLER
#define include_FONTHANDLER

#include <map>
#include <string>

#include "Glyph.hpp"
#include "..\Internal Dependencies\pugixml.hpp"

class FontHandler
{
public:
	FontHandler();

	std::map<std::string, Glyph> m_alphabet;
	Glyph getGlyph(char character);
};

#endif