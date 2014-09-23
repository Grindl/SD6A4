#define  WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>

#include "Particle.hpp"
#include <stdlib.h>
#include <math.h>

#include "Memory Manager/MemoryManager.hpp"

Particle::Particle()
{
	m_position = Vector3f(0, 0, -1);
	float xVel = ((float) rand() )/ RAND_MAX - .5f;
	float yVel = ((float) rand() )/ RAND_MAX - .5f;
	float zVel = ((float) rand() )/ RAND_MAX - .5f;
	m_velocity = Vector3f(xVel, yVel, zVel);
	m_velocity.normalize();

	m_shouldBeRemoved = false;
	m_internalTime = 0;
}

Particle::Particle(Vector3f position, Vector3f velocity)
{
	m_position = position;
	m_velocity = velocity;
	m_internalTime = 0;
}

Particle::~Particle()
{
	/*while(!m_constraints.empty())
	{
		Spring* temp = m_constraints.back();
		m_constraints.pop_back();
		delete temp;
	}*/
}

void Particle::update(float deltaSeconds)
{
	m_internalTime += deltaSeconds;

	m_position = m_position + (m_velocity * deltaSeconds);

	Vector3f sigmaForces = Vector3f(0,0,0);
	/*for (unsigned int ii = 0; ii < m_constraints.size(); ii++)
	{
		m_constraints[ii]->update(deltaSeconds);
		sigmaForces = sigmaForces + m_constraints[ii]->m_lastCalculatedForce;
	}*/

	m_velocity = m_velocity + (sigmaForces * deltaSeconds);
			
}

void Particle::render()
{
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glPointSize(5.f);
	glBegin(GL_POINTS);
	{
		//glColor4f(abs(m_velocity.x), abs(m_velocity.y), abs(m_velocity.z), 1.f);
		glColor4f(.9f, .9f, .9f, .9f);
		glVertex3f(m_position.x, m_position.y, m_position.z);
	}
	glEnd();
	glPopMatrix();
}

bool Particle::shouldBeRemoved()
{
	return false;
}