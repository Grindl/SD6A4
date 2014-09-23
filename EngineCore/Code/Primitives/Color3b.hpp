#pragma once
#ifndef include_COLOR3B
#define include_COLOR3B

class Color4f;

class Color3b
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color3b()
	{
		r = 255;
		g = 255;
		b = 255;
	}

	Color3b(Color4f init);

	Color3b(unsigned char red, unsigned char green, unsigned char blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	const bool operator==(const Color3b& rhs) const
	{
		bool isEqual = true;
		isEqual = isEqual && (r == rhs.r);
		isEqual = isEqual && (g == rhs.g);
		isEqual = isEqual && (b == rhs.b);
		return isEqual;
	}
};

#endif