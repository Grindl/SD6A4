#include <map>
#include <string>

#include "..\Internal Dependencies\stb_image.h"

#pragma comment( lib, "opengl32" )

#include "OpenGLFunctions.hpp"
#include "Texture.hpp"

#include "Memory Manager/MemoryManager.hpp"

//extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

std::map<std::string, Texture*> Texture::s_textureRegistry = std::map<std::string, Texture*>();

//From Professor Eiserloh's example
Texture::Texture( const std::string& imageFilePath )
	: m_openGLTextureID( 0 )
	, x(0)
	, y(0)
{
	//glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress( "glGenerateMipmap" );
	std::map<std::string, Texture*>* textureRegistry = GetTextureManager();
	int numComponents = 0; // Filled in for us to indicate how many color/alpha components the image had (e.g. 3=RGB, 4=RGBA)
	int numComponentsRequested = 0; // don't care; we support 3 (RGB) or 4 (RGBA)
	unsigned char* imageData = stbi_load( imageFilePath.c_str(), &x, &y, &numComponents, numComponentsRequested );

	// Enable texturing
	glEnable( GL_TEXTURE_2D );

	// Tell OpenGL that our pixel data is single-byte aligned
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// Ask OpenGL for an unused texName (ID number) to use for this texture
	glGenTextures( 1, (GLuint*) &m_openGLTextureID );

	// Tell OpenGL to bind (set) this as the currently active texture
	glBindTexture( GL_TEXTURE_2D, m_openGLTextureID );

	// Set texture clamp vs. wrap (repeat)
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); // GL_CLAMP or GL_REPEAT
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); // GL_CLAMP or GL_REPEAT

	// Set magnification (texel > pixel) and minification (texel < pixel) filters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR

	// Set MipMap levels
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);

	GLenum bufferFormat = GL_RGBA; // the format our source pixel data is currently in; any of: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, ...
	if( numComponents == 3 )
		bufferFormat = GL_RGB;

	GLenum internalFormat = bufferFormat; // the format we want the texture to me on the card; allows us to translate into a different texture format as we upload to OpenGL

	glTexImage2D(			// Upload this pixel data to our new OpenGL texture
		GL_TEXTURE_2D,		// Creating this as a 2d texture
		0,					// Which mipmap level to use as the "root" (0 = the highest-quality, full-res image), if mipmaps are enabled
		internalFormat,		// Type of texel format we want OpenGL to use for this texture internally on the video card
		x,			// Texel-width of image; for maximum compatibility, use 2^N + 2^B, where N is some integer in the range [3,10], and B is the border thickness [0,1]
		y,			// Texel-height of image; for maximum compatibility, use 2^M + 2^B, where M is some integer in the range [3,10], and B is the border thickness [0,1]
		0,					// Border size, in texels (must be 0 or 1)
		bufferFormat,		// Pixel format describing the composition of the pixel data in buffer
		GL_UNSIGNED_BYTE,	// Pixel color components are unsigned bytes (one byte per color/alpha channel)
		imageData );		// Location of the actual pixel data bytes/buffer

	//glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free( imageData );

	(*textureRegistry)[ imageFilePath ] = this;
}

Texture* Texture::CreateOrGetTexture(const std::string& imageFilePath)
{
	Texture* requestedTexture;
	if(s_textureRegistry.find(imageFilePath) != s_textureRegistry.end())
	{
		requestedTexture = s_textureRegistry[imageFilePath];
	}
	else
	{
		requestedTexture = new Texture(imageFilePath);
		//s_textureRegistry[imageFilePath] = requestedTexture; not necessary since the constructor does it for us
	}
	return requestedTexture;
}

Texture* Texture::GetTextureByName(const std::string& imageFilePath)
{
	Texture* requestedTexture = 0;
	if(s_textureRegistry.find(imageFilePath) != s_textureRegistry.end())
	{
		requestedTexture = s_textureRegistry[imageFilePath];
	}
	else
	{
		int TEXTURENOTFOUND  = 0;
	}

	return requestedTexture;
}

std::map<std::string, Texture*>* Texture::GetTextureManager()
{
	
	return &s_textureRegistry;
}