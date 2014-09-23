#include <cstdio>


#include "OpenGLFunctions.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

#include "Memory Manager/MemoryManager.hpp"

//TODO: IN the filename of the vertex and fragment shaders, respectively
//TODO: break this into separate functions
//TODO: abstract out all opengl calls
Renderer::Renderer()
{
	initOpenGLFunctions();
	m_fatalError = false;

	//TODO the renderer probably doesn't need to know about the light buffer ID after it's done
	m_lightManager = LightManager();
	glGenBuffers(1, &m_uniformBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(CompactLight)*16, 0, GL_STREAM_DRAW);
	m_lightManager.m_lightBufferID = m_uniformBufferID;


	m_defaultShaderProgram = Shader();
	m_shaderID = m_defaultShaderProgram.m_shaderID;
	glUseProgram(m_shaderID);
	
	m_lightManager.updateLightsInOpenGL(m_shaderID);
	m_singleFrameBuffer = FrameBuffer();


}

