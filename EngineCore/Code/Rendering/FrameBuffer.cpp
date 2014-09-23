#include "FrameBuffer.hpp"

#include "Memory Manager/MemoryManager.hpp"

//HACK this is typically game-centric data, but is now here; perhaps put it in renderer instead?
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;

const char* FBOFragmentShader = ".\\Code\\Shaders\\FixedFunctionFBO.fragment.glsl";
const char* FBOVertexShader = ".\\Code\\Shaders\\FixedFunctionFBO.vertex.glsl";

//----------------------------------------------------------------------------------------
FrameBuffer::FrameBuffer()
{
	m_frameBufferObject = 0;
	m_framebufferColorTexture = 0;
	m_framebufferDepthTexture = 0;
	m_framebufferColorLocation = 0;
	m_framebufferDepthLocation = 0;

	m_FBOShader = Shader(FBOVertexShader, FBOFragmentShader);
	glUseProgram(m_FBOShader.m_shaderID);
	//BEGIN SQUIRRELCODE
	/////////////////////////////////////////////////////////////////////////////
	// FRAMEBUFFER OBJECT INITIALIZATION (RUN ONCE AT STARTUP)
	/////////////////////////////////////////////////////////////////////////////

	// Create color framebuffer texture
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures( 1, &m_framebufferColorTexture );
	glBindTexture( GL_TEXTURE_2D, m_framebufferColorTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );

	// Create depth framebuffer texture
	glActiveTexture( GL_TEXTURE1 );
	glGenTextures( 1, &m_framebufferDepthTexture );
	glBindTexture( GL_TEXTURE_2D, m_framebufferDepthTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL );

	// Create an FBO (Framebuffer Object) and activate it
	glGenFramebuffers( 1, &m_frameBufferObject );
	glBindFramebuffer( GL_FRAMEBUFFER, m_frameBufferObject );

	// Attach our color and depth textures to the FBO, in the color0 and depth FBO "slots"
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebufferColorTexture, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_framebufferDepthTexture, 0);
	//END SQUIRRELCODE

	m_framebufferColorLocation = glGetUniformLocation(m_FBOShader.m_shaderID, "u_diffuseTexture");
	m_framebufferDepthLocation = glGetUniformLocation(m_FBOShader.m_shaderID, "u_depthTexture");
}

//----------------------------------------------------------------------------------------
void FrameBuffer::preRenderStep()
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_frameBufferObject );
}

//----------------------------------------------------------------------------------------
void FrameBuffer::postRenderStep()
{
	glPushMatrix();
	glBindFramebuffer( GL_FRAMEBUFFER, 0 ); // Not drawing to the FBO anymore; now we're rendering to framebuffer for real
	//Prepare for simple 2D ortho drawing:
	glClearColor( 0.35f, 0.35f, 0.35f, 1.f );
	glClearDepth( 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glDisable( GL_DEPTH_TEST );
	//glDepthMask( GL_FALSE );
	glOrtho( 0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0 ); // or equivalent in your own matrix stack

	glUseProgram( m_FBOShader.m_shaderID ); // Use a totally different shader program to perform your framebuffer effects

	// Bind your two FBO textures now as INPUTS into the framebuffer effect shader, and pass them in (as uniforms, per usual):
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, m_framebufferDepthTexture );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_framebufferColorTexture );

	glUniform1i( m_framebufferColorLocation, 0 ); // Use the already-rendered scene's color data as a simple texture, as you please
	glUniform1i( m_framebufferDepthLocation, 1 ); // Use the already-rendered scene's depth data as a simple texture, as you please
	int shaderTime = glGetUniformLocation(m_FBOShader.m_shaderID, "u_time");
	//HACK internal time should be accessed elsewhere, perhaps set up time utility to tick and keep its own universal time
	float m_internalTime = .1f;
	glUniform1f(shaderTime, m_internalTime);

	glBegin(GL_QUADS);
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0, 0);
		glVertex2f(0,0);

		glTexCoord2f(1,0);
		glVertex2f(SCREEN_WIDTH,0);

		glTexCoord2f(1, 1);
		glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);

		glTexCoord2f(0, 1);
		glVertex2f(0,SCREEN_HEIGHT);
	}
	glEnd();

	glPopMatrix();
}