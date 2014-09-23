#include "Color3b.hpp"
#include "Color4f.hpp"

Color3b::Color3b(Color4f init)
{
	r = (unsigned char)(init.red*255);
	g = (unsigned char)(init.green*255);
	b = (unsigned char)(init.blue*255);
}