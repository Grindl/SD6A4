#include "XMLParser.hpp"

#include <vector>
#include "StringUtility.hpp"

#include "Memory Manager/MemoryManager.hpp"

//------------------------------------------------------------------------------
XMLParser::XMLParser()
{

}


//------------------------------------------------------------------------------
int XMLParser::GetIntXMLAttribute(pugi::xml_node element, std::string attributeName, int defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	int foundValue = foundAttribute.as_int(defaultValue);
	return foundValue;
}

//------------------------------------------------------------------------------
float XMLParser::GetFloatXMLAttribute(pugi::xml_node element, std::string attributeName, float defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	float foundValue = foundAttribute.as_float(defaultValue);
	return foundValue;
}

//------------------------------------------------------------------------------
std::string XMLParser::GetStringXMLAttribute(pugi::xml_node element, std::string attributeName, std::string defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	std::string foundValue = foundAttribute.as_string(defaultValue.c_str());
	return foundValue;
}

//------------------------------------------------------------------------------
Color4f XMLParser::GetColorXMLAttribute(pugi::xml_node element, std::string attributeName, Color4f defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	std::string intermediadeValue = foundAttribute.as_string("");

	Color4f foundValue;
	if(intermediadeValue == "")
	{
		foundValue = defaultValue;
	}
	else
	{
		foundValue = Color4f(intermediadeValue);
	}

	return foundValue;
}

//------------------------------------------------------------------------------
Vector2f XMLParser::GetVector2fXMLAttribute(pugi::xml_node element, std::string attributeName, Vector2f defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	std::string intermediadeValue = foundAttribute.as_string("");

	Vector2f foundValue;
	if(intermediadeValue == "")
	{
		foundValue = defaultValue;
	}
	else
	{
		foundValue = Vector2f(intermediadeValue);
	}

	return foundValue;
}

//------------------------------------------------------------------------------
Vector2i XMLParser::GetVector2XMLAttribute(pugi::xml_node element, std::string attributeName, Vector2i defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	std::string intermediadeValue = foundAttribute.as_string("");

	Vector2i foundValue;
	if(intermediadeValue == "")
	{
		foundValue = defaultValue;
	}
	else
	{
		foundValue = Vector2i(intermediadeValue);
	}

	return foundValue;
}

//------------------------------------------------------------------------------
Vector3f XMLParser::GetVector3fXMLAttribute(pugi::xml_node element, std::string attributeName, Vector3f defaultValue)
{
	pugi::xml_attribute foundAttribute = element.attribute(attributeName.c_str());
	std::string intermediadeValue = foundAttribute.as_string("");

	Vector3f foundValue;
	if(intermediadeValue == "")
	{
		foundValue = defaultValue;
	}
	else
	{
		foundValue = Vector3f(intermediadeValue);
	}

	return foundValue;
}

//------------------------------------------------------------------------------
bool XMLParser::ValidateXMLAttribute(pugi::xml_node element, std::string requiredAttributes, std::string optionalAttributes)
{
	//TODO this assumes at least one attribute exists
	bool isValidXMLAttributes = true;
	std::vector<std::string> requiredAttributesSubstringed;
	std::vector<bool> requiredAttributeFound;
	std::vector<std::string> optionalAttributesSubstringed;

	std::string currenAttributeNameString = "";
	for(unsigned int ii = 0; ii < requiredAttributes.size(); ii++)
	{
		std::string currenCharacter = requiredAttributes.substr(ii, 1);
		if(currenCharacter == " ")
		{
			//do nothing
		}
		else if(currenCharacter == ",")
		{
			requiredAttributesSubstringed.push_back(currenAttributeNameString);
			requiredAttributeFound.push_back(false);
			currenAttributeNameString = "";
		}
		else
		{
			currenAttributeNameString.append(currenCharacter);
		}
	}
	if (currenAttributeNameString != "")
	{
		requiredAttributesSubstringed.push_back(currenAttributeNameString);
		requiredAttributeFound.push_back(false);
	}
	currenAttributeNameString = "";
	for(unsigned int ii = 0; ii < optionalAttributes.size(); ii++)
	{
		std::string currenCharacter = optionalAttributes.substr(ii, 1);
		if(currenCharacter == " ")
		{
			//do nothing
		}
		else if(currenCharacter == ",")
		{
			optionalAttributesSubstringed.push_back(currenAttributeNameString);
			currenAttributeNameString = "";
		}
		else
		{
			currenAttributeNameString.append(currenCharacter);
		}
	}
	if (currenAttributeNameString != "")
	{
		optionalAttributesSubstringed.push_back(currenAttributeNameString);
	}
	pugi::xml_attribute firstAttribute = element.first_attribute();
	pugi::xml_attribute currentAttribute = firstAttribute;
	while (currentAttribute != 0) 
	{
		bool recognizedAttributeType = false;
		for(unsigned int ii = 0; ii < requiredAttributesSubstringed.size(); ii++)
		{
			if(currentAttribute.name() == requiredAttributesSubstringed[ii])
			{
				recognizedAttributeType = true;
				requiredAttributeFound[ii] = true;
			}
		}
		for (unsigned int ii = 0; ii < optionalAttributesSubstringed.size(); ii++)
		{
			if(currentAttribute.name() == optionalAttributesSubstringed[ii])
			{
				recognizedAttributeType = true;
			}
		}

		if(!recognizedAttributeType)
		{
			//TODO ASSERT MessageBoxA(NULL, infoLog2, "ERROR", MB_OK);
			isValidXMLAttributes = false;
		}
		currentAttribute = currentAttribute.next_attribute();
	}
	bool allRequiredAttributesFound = true;
	for (unsigned int ii = 0; ii < requiredAttributeFound.size(); ii++)
	{
		if(requiredAttributeFound[ii] == false)
		{
			allRequiredAttributesFound = false;
		}
	}

	if (!allRequiredAttributesFound)
	{
		//TODO ASSERT
		isValidXMLAttributes = false;
	}

	return isValidXMLAttributes;
}

//------------------------------------------------------------------------------
bool XMLParser::ValidateXMLChildElements(pugi::xml_node element, std::string requiredChildElements, std::string optionalChildElements)
{
	//TODO this assumes at least one child exists
	bool isValidXMLChildren = true;
	std::vector<std::string> requiredChildrenSubstringed;
	std::vector<bool> requiredChildFound;
	std::vector<std::string> optionalChildrenSubstringed;

	std::string currentChildString = "";
	for(unsigned int ii = 0; ii < requiredChildElements.size(); ii++)
	{
		std::string currenCharacter = requiredChildElements.substr(ii, 1);
		if(currenCharacter == " ")
		{
			//do nothing
		}
		else if(currenCharacter == ",")
		{
			requiredChildrenSubstringed.push_back(currentChildString);
			requiredChildFound.push_back(false);
			currentChildString = "";
		}
		else
		{
			currentChildString.append(currenCharacter);
		}
	}
	if (currentChildString != "")
	{
		requiredChildrenSubstringed.push_back(currentChildString);
		requiredChildFound.push_back(false);
	}

	optionalChildrenSubstringed = StringUtility::StringSplit(optionalChildElements, ",", " ");


	pugi::xml_node firstChild = element.first_child();
	pugi::xml_node currentChild = firstChild;
	while (currentChild != 0)
	{
		bool recognizedChildType = false;
		for(unsigned int ii = 0; ii < requiredChildrenSubstringed.size(); ii++)
		{
			if(currentChild.name() == requiredChildrenSubstringed[ii])
			{
				recognizedChildType = true;
				requiredChildFound[ii] = true;
			}
		}
		for (unsigned int ii = 0; ii < optionalChildrenSubstringed.size(); ii++)
		{
			if(currentChild.name() == optionalChildrenSubstringed[ii])
			{
				recognizedChildType = true;
			}
		}

		if(!recognizedChildType)
		{
			//TODO ASSERT
			isValidXMLChildren = false;
		}
		currentChild = currentChild.next_sibling();
	} 

	bool allRequiredChildrenFound = true;
	for (unsigned int ii = 0; ii < requiredChildFound.size(); ii++)
	{
		if(requiredChildFound[ii] == false)
		{
			allRequiredChildrenFound = false;
		}
	}

	if (!allRequiredChildrenFound)
	{
		//TODO ASSERT
		isValidXMLChildren = false;
	}

	return isValidXMLChildren;
}


//-----------------------------------------------------------------------------
void UnitTestXMLParser(std::string filename)
{
	pugi::xml_document fileIn;
	pugi::xml_parse_result fileResult = fileIn.load_file(filename.c_str());
	pugi::xml_node firstNodeData = fileIn.first_child();
	pugi::xml_node currentNodeData = firstNodeData;

	//XMLParser myXMLTester = XMLParser();

	bool rootIsValid = XMLParser::ValidateXMLChildElements(currentNodeData, "Bear", "Car, Person");
	currentNodeData = currentNodeData.first_child();

	bool bearChildrenIsValid = XMLParser::ValidateXMLChildElements(currentNodeData, "", "Person");
	bool bearAttributesIsValid = XMLParser::ValidateXMLAttribute(currentNodeData, "Age", "Hunger, Speed");
	std::string bearHungerTester = XMLParser::GetStringXMLAttribute(currentNodeData, "Hunger", "Not");
	float bearSpeed = XMLParser::GetFloatXMLAttribute(currentNodeData, "Speed");
	currentNodeData = currentNodeData.next_sibling();

	bool carChildrenIsValid = XMLParser::ValidateXMLChildElements(currentNodeData, "", "Person");
	bool carAttributesIsValid = XMLParser::ValidateXMLAttribute(currentNodeData, "Age", "Hunger, Speed");
	int carAge = XMLParser::GetIntXMLAttribute(currentNodeData, "Age");

}

pugi::xml_node XMLParser::GetRootNodeFromFile(std::string fileName)
{
	pugi::xml_document* fileIn = new pugi::xml_document();
	pugi::xml_parse_result fileResult = fileIn->load_file(fileName.c_str());
	pugi::xml_node firstNodeData = fileIn->first_child();
	return firstNodeData;
}