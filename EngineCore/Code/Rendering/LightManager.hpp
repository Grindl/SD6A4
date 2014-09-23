#pragma once
#ifndef include_LIGHTMANAGER
#define include_LIGHTMANAGER


#include "Light.hpp"

class LightManager
{
public:
	LightManager();
		
	static const int NUMBER_OF_LIGHTS_SUPPORTED = 16;

	Light* m_lights[NUMBER_OF_LIGHTS_SUPPORTED];
	unsigned int m_lightBufferID;

	void update(float deltaSeconds);
	void updateLightsInOpenGL(unsigned int shaderID);
};

#endif