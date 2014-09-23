#include "Camera.hpp"
#include "Rendering\OpenGLFunctions.hpp"
#include <gl/glu.h>

//----------------------------------------------------------------------------------------
Camera::Camera()
{
	m_cameraMode = ORTHO;
	m_aspectRatio = 16.f/9.f;
	m_fieldOfView = 40.f;
	m_nearClip = .01f;
	m_farClip = 500.f;
	m_screenDimensionsInPixels = Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_position = Vector3f(0.f, 0.f, 0.f);
	m_orientationDegrees = Vector3f(0.f, 0.f, 0.f);
	m_cameraSizeInWorldUnits = Vector2f(500.f*m_aspectRatio, 500.f);
}

//----------------------------------------------------------------------------------------
void Camera::preRenderStep()
{
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f );
	//glClearDepth(1.f);
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	if(m_cameraMode == PERSPECTIVE)
	{
		gluPerspective(m_fieldOfView, m_aspectRatio, m_nearClip, m_farClip);
		glRotatef(-90.f, 1.f, 0.f, 0.f);
		glRotatef(-1.f*m_orientationDegrees.x, 0.f, 0.f, 1.f);
		glRotatef(-1.f*m_orientationDegrees.y, cos(m_orientationDegrees.x*(PI/180.f)), sin(m_orientationDegrees.x*(PI/180.f)), 0.f);
	}
	if(m_cameraMode == ORTHO)
	{
		glOrtho(0.0, m_cameraSizeInWorldUnits.x, 0.0, m_cameraSizeInWorldUnits.y, 0, 1);
	}

	glTranslatef(-1.f*m_position.x, -1.f*m_position.y, -1.f*m_position.z);

	glUseProgram(0);
}

//----------------------------------------------------------------------------------------
void Camera::postRenderStep()
{
	glPopMatrix();
}