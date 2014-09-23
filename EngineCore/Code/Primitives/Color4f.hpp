#pragma once
#ifndef include_COLOR4F
#define include_COLOR4F

#include <string>

class Color3b;

class Color4f
{
public:
	float red;
	float green;
	float blue;
	float alphaValue;

	Color4f()
		:red(1.f)
		,green(1.f)
		,blue(1.f)
		,alphaValue(1.f)
	{
	}

	Color4f(float r, float g, float b, float a)
		:red(r)
		,green(g)
		,blue(b)
		,alphaValue(a)
	{
	}

	Color4f(Color3b initColor);

	Color4f(std::string initString)
	{
		//char* intermediateParse[4];
		int currentChannel = 0;
		std::string currenChannelString = "";
		for(unsigned int ii = 0; ii < initString.size(); ii++)
		{
			std::string currenCharacter = initString.substr(ii, 1);
			if(currenCharacter == " ")
			{
				//do nothing
			}
			else if(currenCharacter == ",")
			{
				switch(currentChannel)
				{
				case 0:
					red = (float) atof(currenChannelString.c_str());
					break;
				case 1:
					green = (float) atof(currenChannelString.c_str());
					break;
				case 2: 
					blue = (float) atof(currenChannelString.c_str());
					break;
				case 3:
					alphaValue = (float) atof(currenChannelString.c_str());
					break;
				default:
					//TODO: ASSERT
					break;
				}
				currentChannel++;
				currenChannelString = "";
			}
			else
			{
				currenChannelString.append(currenCharacter);
			}
			if(currenChannelString != "")
			{
				alphaValue = (float) atof(currenChannelString.c_str());
			}
		}
	}
};



namespace COLOR
{
	const Color4f RED =			Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	const Color4f GREEN =		Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	const Color4f BLUE =		Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	const Color4f GREY =		Color4f(0.6f, 0.6f, 0.6f, 1.0f);
	const Color4f WHITE =		Color4f(1.0f, 1.0f, 1.0f, 1.0f);
	const Color4f BLACK =		Color4f(0.0f, 0.0f, 0.0f, 1.0f);
	const Color4f CLEAR =		Color4f(0.0f, 0.0f, 0.0f, 0.0f);
}


#endif