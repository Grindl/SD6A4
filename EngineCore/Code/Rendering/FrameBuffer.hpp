#pragma once
#ifndef include_FRAMEBUFFER
#define include_FRAMEBUFFER

#include "Shader.hpp"

class FrameBuffer
{
public:
	FrameBuffer();

	Shader m_FBOShader;
	GLuint m_frameBufferObject;
	GLuint m_framebufferColorTexture;
	GLuint m_framebufferDepthTexture;
	GLint m_framebufferColorLocation;
	GLint m_framebufferDepthLocation;

	void preRenderStep();
	void postRenderStep();
};


#endif