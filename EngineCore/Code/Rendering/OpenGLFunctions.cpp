//#include "OpenGLFunctions.hpp" intentionally excluded
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "..\Internal Dependencies\glext.h"

#pragma comment( lib, "opengl32" )

#include "Memory Manager/MemoryManager.hpp"

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

void initOpenGLFunctions()
{
	static bool alreadyInitialized = false;
	if(!alreadyInitialized)
	{
		glGenBuffers		 = (PFNGLGENBUFFERSPROC) wglGetProcAddress( "glGenBuffers" );
		glBindBuffer		 = (PFNGLBINDBUFFERPROC) wglGetProcAddress( "glBindBuffer" );
		glBufferData		 = (PFNGLBUFFERDATAPROC) wglGetProcAddress( "glBufferData" );
		glCreateShader		 = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
		glShaderSource		 = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
		glCompileShader		 = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
		glGetShaderiv		 = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
		glAttachShader		 = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
		glCreateProgram		 = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
		glLinkProgram		 = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
		glGetProgramiv		 = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
		glUseProgram		 = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
		glUniform1f			 = (PFNGLUNIFORM1FPROC) wglGetProcAddress("glUniform1f");
		glUniform1i			 = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
		glActiveTexture		 = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
		glGetShaderInfoLog	 = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
		glGetProgramInfoLog  = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");
		glVertexAttribPointer= (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) wglGetProcAddress("glBindAttribLocation");
		glUniform4fv		 = (PFNGLUNIFORM4FVPROC) wglGetProcAddress("glUniform4fv");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glEnableVertexAttribArray");
		glGetAttribLocation  = (PFNGLGETATTRIBLOCATIONPROC) wglGetProcAddress("glGetAttribLocation");
		glUniformMatrix4fv	 = (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");
		glUniform3f			 = (PFNGLUNIFORM3FPROC) wglGetProcAddress("glUniform3f");
		glDeleteBuffers		 = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffers");
		glUniformBlockBinding= (PFNGLUNIFORMBLOCKBINDINGPROC) wglGetProcAddress("glUniformBlockBinding");
		glBindBufferBase	 = (PFNGLBINDBUFFERBASEPROC) wglGetProcAddress("glBindBufferBase");
		glGetUniformBlockIndex=(PFNGLGETUNIFORMBLOCKINDEXPROC) wglGetProcAddress("glGetUniformBlockIndex");
		glBufferSubData		 = (PFNGLBUFFERSUBDATAPROC) wglGetProcAddress("glBufferSubData");
		glUniform1fv		 = (PFNGLUNIFORM1FVPROC) wglGetProcAddress("glUniform1fv");
		glGenFramebuffers	 = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
		glBindFramebuffer	 = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
		glFramebufferTexture2D=(PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
	}
	alreadyInitialized = true;
}
