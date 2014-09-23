#include "Vector2f.hpp"
#include "Vector2i.hpp"
#include "../Utility/StringUtility.hpp"

#include "Memory Manager/MemoryManager.hpp"

Vector2f::Vector2f()
	:x(0)
	,y(0)
{
}
Vector2f::Vector2f(float a, float b)
	:x(a)
	,y(b)
{
}
Vector2f::Vector2f(float c[2])
	:x(c[0])
	,y(c[1])
{
}

Vector2f::Vector2f(const std::string& initString)
{
	std::vector<std::string> dividedString = StringUtility::StringSplit(initString, ",", " ");
	if(dividedString.size() != 2)
	{
		//TODO assert
	}
	else
	{
		x = (float)atof(dividedString[0].c_str());
		y = (float)atof(dividedString[1].c_str());
	}
}

Vector2f::Vector2f(const Vector2i& conversion)
{
	x = (float)conversion.x;
	y = (float)conversion.y;
}