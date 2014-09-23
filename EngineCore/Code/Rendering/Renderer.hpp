#pragma once
#ifndef include_RENDERER
#define include_RENDERER

#define WIN32_LEAN_AND_MEAN

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "..\Internal Dependencies\glext.h"
#include "LightManager.hpp"
#include "..\Primitives\RenderVector.hpp"
#include "Shader.hpp"
#include "FrameBuffer.hpp"

class Renderer
{
public:
	Renderer();

	unsigned int m_textureID;
	unsigned int m_shaderID;
	unsigned int m_uniformBufferID;
	bool m_fatalError;
	LightManager m_lightManager;
	Shader m_defaultShaderProgram;
	FrameBuffer m_singleFrameBuffer;
};


#endif