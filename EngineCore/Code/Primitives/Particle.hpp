#pragma once
#ifndef include_PARTICLE
#define	include_PARTICLE

#include "Element.hpp"
#include "Vector3f.hpp"
//#include "Spring.hpp"
//#include <vector>

class Particle : public Element
{
public:
	Particle();
	Particle(Vector3f position, Vector3f velocity);
	~Particle();
	
	Vector3f m_position;
	Vector3f m_previousPosition;
	Vector3f m_velocity;
	Vector3f m_previousVelocity;
	float m_internalTime;
	//std::vector<Spring*> m_constraints;


	virtual void update(float deltaSeconds);
	virtual void render();
	virtual bool shouldBeRemoved();
};


#endif