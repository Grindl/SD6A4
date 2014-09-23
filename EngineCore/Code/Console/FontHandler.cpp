#include "FontHandler.hpp"
#include "..\Rendering\Texture.hpp"

#include "Memory Manager/MemoryManager.hpp"

FontHandler::FontHandler()
{
	pugi::xml_document fileIn;
	pugi::xml_parse_result alphabetResult = fileIn.load_file(".\\Data\\MainFont_EN.FontDef.xml");
	pugi::xml_node firstGlyphData = fileIn.first_child().first_child().next_sibling("Glyph");
	pugi::xml_node currentGlyphData = firstGlyphData;
	Texture fontSheet = *(Texture::CreateOrGetTexture(".\\Data\\MainFont_EN_00.png"));

	do
	{
		Glyph nextGlyph = Glyph();
		
		nextGlyph.m_textureSheetID = fontSheet.m_openGLTextureID;
		nextGlyph.m_fontName = "Calibri";

		char characterSymbol[2];
		characterSymbol[0] = currentGlyphData.attribute("ucsIndex").as_uint();
		characterSymbol[1] = 0;
		std::string stringSymbol = std::string(characterSymbol);
		nextGlyph.m_textValue = stringSymbol;

		std::string texMins = currentGlyphData.attribute("texCoordMins").as_string();
		std::string texMaxs = currentGlyphData.attribute("texCoordMaxs").as_string();
		Vector2f minsAsVec = Vector2f(texMins);
		Vector2f maxsAsVec = Vector2f(texMaxs);
		Vector2f sizeAsVec = maxsAsVec - minsAsVec;

		nextGlyph.m_bottomLeftTextureCoord = minsAsVec;
		nextGlyph.m_height = sizeAsVec.y;
		nextGlyph.m_widthInTexture = sizeAsVec.x;

		nextGlyph.m_widthRelative = currentGlyphData.attribute("ttfB").as_float();
		nextGlyph.m_leadingSpaceRelative = currentGlyphData.attribute("ttfA").as_float();
		nextGlyph.m_trailingSpaceRelative = currentGlyphData.attribute("ttfC").as_float();

		m_alphabet[stringSymbol] = nextGlyph;
		currentGlyphData = currentGlyphData.next_sibling("Glyph");
	}
	while(currentGlyphData != firstGlyphData && currentGlyphData.root() != NULL);

}

Glyph FontHandler::getGlyph(char character)
{
	std::string temp = std::string(&character);
	return m_alphabet.at(temp);
}