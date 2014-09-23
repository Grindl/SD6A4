#pragma once
#ifndef include_TEXTURE
#define include_TEXTURE


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "..\Internal Dependencies\glext.h"
#include <map>

#pragma comment( lib, "opengl32" )
#pragma comment( lib, "glu32" )

#include "..\Internal Dependencies\stb_image.h"

;



class Texture
{
public:
	//PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	//TODO make a deconstructor/delete that will free up system and graphics card memory and that also automatically deletes the entire texture registry on exit
	static std::map<std::string, Texture*> s_textureRegistry;
	GLuint m_openGLTextureID;
	int x;
	int y;

	Texture(const std::string& imageFilePath);

	static Texture* GetTextureByName(const std::string& imageFilePath);
	static Texture* CreateOrGetTexture(const std::string& imageFilePath);
	static std::map<std::string, Texture*>* Texture::GetTextureManager();
	
};

#endif
