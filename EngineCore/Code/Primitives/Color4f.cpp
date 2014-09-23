#include "Color4f.hpp"
#include "Color3b.hpp"

Color4f::Color4f(Color3b initColor)
{
	red = initColor.r /255.f;
	green = initColor.g / 255.f;
	blue = initColor.b /255.f;
	alphaValue = 1.f;
}