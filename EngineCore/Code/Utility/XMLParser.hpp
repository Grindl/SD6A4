#pragma once
#ifndef include_XMLPARSER
#define include_XMLPARSER

#include <string>

#include "..\Internal Dependencies\pugixml.hpp"
#include "..\Primitives\Color4f.hpp"
#include "..\Primitives\Vector2f.hpp"
#include "..\Primitives\Vector2i.hpp"
#include "..\Primitives\Vector3f.hpp"

class XMLParser
{
public:
	XMLParser();

	// Support each of these types, or its equivalent: int, float, string, Rgba, Vector2, IntVector2, Vector3, IntVector3
	static int GetIntXMLAttribute(pugi::xml_node element, std::string attributeName, int defaultValue=0);
	static float GetFloatXMLAttribute(pugi::xml_node element, std::string attributeName, float defaultValue=0.f);
	static std::string GetStringXMLAttribute(pugi::xml_node element, std::string attributeName, std::string defaultValue="");
	static Color4f GetColorXMLAttribute(pugi::xml_node element, std::string attributeName, Color4f defaultValue=Color4f(1.f, 1.f, 1.f, 1.f));
	static Vector2f GetVector2fXMLAttribute(pugi::xml_node element, std::string attributeName, Vector2f defaultValue=Vector2f(0.f, 0.f));
	static Vector2i GetVector2XMLAttribute(pugi::xml_node element, std::string attributeName, Vector2i defaultValue=Vector2i(0, 0));
	static Vector3f GetVector3fXMLAttribute(pugi::xml_node element, std::string attributeName, Vector3f defaultValue=Vector3f(0.f, 0.f, 0.f));
 
	static bool ValidateXMLAttribute(pugi::xml_node element, std::string requiredAttributes, std::string optionalAttributes);
	static bool ValidateXMLChildElements(pugi::xml_node element, std::string requiredChildElements, std::string optionalChildElements);

	static pugi::xml_node GetRootNodeFromFile(std::string fileName);

};

void UnitTestXMLParser(std::string filename);

#endif