#pragma once
#ifndef include_RVector
#define include_RVector


struct RenderVector
{
public:
	float renderData[9]; 
	//0 1 2 position XYZ
	//3 4 5 6 RGBA
	//7 8 texture UV
};

#endif