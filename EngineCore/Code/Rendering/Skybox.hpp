#pragma  once
#ifndef include_SKYBOX
#define include_SKYBOX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment( lib, "opengl32" )
#pragma comment( lib, "glu32" )

#include "Texture.hpp"

class Skybox
{
public:
	Texture* m_skyTexture;
	GLuint m_textureID;

	Skybox();
	const void render();
};



Skybox::Skybox()
{
	m_skyTexture = new Texture(".\\Data\\interstellar_large.jpg");
	m_textureID = m_skyTexture->m_openGLTextureID;

}

const void Skybox::render()
{
	const float TEXWIDTH = .25f;
	const float TEXHEIGHT = 1.f/3.f;
	glDepthMask(false);
	glPushMatrix();
	glScalef(10.f, 10.f, 10.f);
	glTranslatef(-.5f, -.5f, -.5f);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glBegin(GL_QUADS);
	{
		glColor3f(1.f, 1.f, 1.f);

		//west
		glTexCoord2f((0.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 0.f);
		glTexCoord2f((0.f+1.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 0.f);
		glTexCoord2f((0.f+1.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 1.f);
		glTexCoord2f((0.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 1.f);

		//north
		glTexCoord2f((1.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 0.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 0.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f((1.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 1.f);

		//east
		glTexCoord2f((2.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 0.f);
		glTexCoord2f((2.f+1.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 0.f);
		glTexCoord2f((2.f+1.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 1.f);
		glTexCoord2f((2.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 1.f);

		//south
		glTexCoord2f((3.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 0.f);
		glTexCoord2f((3.f+1.f)*TEXWIDTH, (1.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 0.f);
		glTexCoord2f((3.f+1.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 1.f);
		glTexCoord2f((3.f)*TEXWIDTH, (1.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 1.f);

		//up
		glTexCoord2f((1.f)*TEXWIDTH, (0.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 1.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (0.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (0.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 1.f);
		glTexCoord2f((1.f)*TEXWIDTH, (0.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 1.f);

		//down
		glTexCoord2f((1.f)*TEXWIDTH, (2.f+1.f)*TEXHEIGHT);
		glVertex3f(0.f, 0.f, 0.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (2.f+1.f)*TEXHEIGHT);
		glVertex3f(1.f, 0.f, 0.f);
		glTexCoord2f((1.f+1.f)*TEXWIDTH, (2.f)*TEXHEIGHT);
		glVertex3f(1.f, 1.f, 0.f);
		glTexCoord2f((1.f)*TEXWIDTH, (2.f)*TEXHEIGHT);
		glVertex3f(0.f, 1.f, 0.f);
	}
	glEnd();
	glPopMatrix();
	glDepthMask(true);
}


#endif