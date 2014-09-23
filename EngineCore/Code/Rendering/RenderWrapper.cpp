#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "..\Internal Dependencies\glext.h"
#include "OpenGLFunctions.hpp"

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include "RenderWrapper.hpp"

#include "Memory Manager/MemoryManager.hpp"

//TODO standalone functions for all openGL functions

void RWGenBuffers(int numBuffers, unsigned int* ptrToFirstBuffer)
{
	glGenBuffers(numBuffers, ptrToFirstBuffer);
}

void RWBindBuffer(RWEnum targetType, unsigned int bufferID)
{
	glBindBuffer(targetType, bufferID);
}