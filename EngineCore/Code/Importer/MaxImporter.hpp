#pragma once
#ifndef include_MAXIMPORTER
#define include_MAXIMPORTER

#include "..\Primitives\RenderVector.hpp"
#include "..\Primitives\VertexData.hpp"
#include "..\Debug Graphics\DebugMultiPoly.hpp"

class MaxImporter
{
public:
	MaxImporter();

	//returns a pointer to a RenderVector Array on the heap of size out_size
	static RenderVector* ImportFrom3DSMaxToRenderVector(const std::string& fileName, int& out_size);
	//returns a pointer to a VertexData array on the heap of size out_size
	static VertexData* ImportFrom3DSMaxToVertexData(const std::string& fileName, int& out_size);
	//returns a pointer to a full multi-VBO debug object
	static DebugMultiPoly* ImportFrom3DSMaxToDebugMultiPoly(const std::string& fileName);

};

#endif