#include <vector>

#include "Vector2i.hpp"
#include "Vector2f.hpp"
#include "../Utility/StringUtility.hpp"

#include "Memory Manager/MemoryManager.hpp"

//------------------------------------------------------------------------------
Vector2i::Vector2i()
	:x(0)
	,y(0)
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(int a, int b)
	:x(a)
	,y(b)
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(int c[2])
	:x(c[0])
	,y(c[1])
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const std::string& initString)
{
	std::vector<std::string> dividedString = StringUtility::StringSplit(initString, ",", " ");
	if(dividedString.size() != 2)
	{
		//TODO assert
	}
	else
	{
		x = atoi(dividedString[0].c_str());
		y = atoi(dividedString[1].c_str());
	}
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const Vector2f& conversion)
{
	x = (int)conversion.x;
	y = (int)conversion.y;
}