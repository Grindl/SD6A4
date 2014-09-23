#include "OpenGLFunctions.hpp"

#include "Light.hpp"

#include "Memory Manager/MemoryManager.hpp"

Light::Light()
{
	genVBO();
	m_timeToLiveSeconds = 0.f;

	m_origin = Vector3f(0,0,2);
	m_firstColor = Color4f(0,0,0,0);
	m_direction = Vector3f(0,0,1);
	m_innerRadius = .00001f;
	m_outerRadius = .00002f;
	m_innerApertureDot = -1.2f;
	m_outerApertureDot = -1.1f;
	m_fractionAmbient = 0.f;
	m_isDirty = true;
	m_blockOffset = 0;
	m_movingLight = true;
}

Light::Light(LIGHT_TYPE type)
{
	//	enum LIGHT_TYPE{INVALID_LIGHT = -1, GLOBAL_POINTLIGHT, LOCAL_POINTLIGHT, LOCAL_SPOTLIGHT, GLOBAL_SPOTLIGHT, 
	//LOCAL_AMBIENTLIGHT, GLOBAL_AMBIENTLIGHT, GLOBAL_DIRECTIONALLIGHT};
	genVBO();
	m_timeToLiveSeconds = 0.f;

	m_origin = Vector3f(0,0,2);
	m_firstColor = Color4f(0,0,0,0);
	m_direction = Vector3f(0,0,1);
	m_innerRadius = .00001f;
	m_outerRadius = .00002f;
	m_innerApertureDot = 1.2f;
	m_outerApertureDot = 1.1f;
	m_fractionAmbient = 0.f;
	m_isDirty = true;
	m_blockOffset = 0;
	m_movingLight = true;
	m_shouldBeDisplayed = true;

	switch(type)
	{
	case GLOBAL_POINTLIGHT:
		{
			m_innerRadius = 100000000.f;
			m_outerRadius = 100001000.f;
			m_innerApertureDot = -1.2f;
			m_outerApertureDot = -1.1f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	case LOCAL_POINTLIGHT:
		{
			m_innerRadius = .5f;
			m_outerRadius = 1.5f;
			m_innerApertureDot = -1.2f;
			m_outerApertureDot = -1.1f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	case LOCAL_SPOTLIGHT:
		{
			m_direction = Vector3f(0,0,1);
			m_innerRadius = 1.f;
			m_outerRadius = 3.f;
			m_innerApertureDot = .8f;
			m_outerApertureDot = .6f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	case GLOBAL_SPOTLIGHT:
		{
			m_direction = Vector3f(0,0,1);
			m_innerRadius = 100000000.f;
			m_outerRadius = 100001000.f;
			m_innerApertureDot = .8f;
			m_outerApertureDot = .6f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	case LOCAL_AMBIENTLIGHT:
		{
			m_innerRadius = 1.f;
			m_outerRadius = 3.f;
			m_innerApertureDot = -1.2f;
			m_outerApertureDot = -1.1f;
			m_fractionAmbient = 1.f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	case GLOBAL_AMBIENTLIGHT:
		{
			m_innerRadius = 100000000.f;
			m_outerRadius = 100001000.f;
			m_innerApertureDot = -1.2f;
			m_outerApertureDot = -1.1f;
			m_fractionAmbient = 1.f;
			m_firstColor = Color4f(1,1,1,1);
			break;
		}
	}
}

void Light::update(float deltaSeconds)
{
	//TODO rename this to be more general and allow for both time to live and internal time for movement
	m_timeToLiveSeconds += 2*deltaSeconds/(m_blockOffset+1);
	if (m_movingLight)
	{
		m_origin = Vector3f(200*sin(m_timeToLiveSeconds*.1f), 200*sin(2*m_timeToLiveSeconds*.1f), 50.f*cos(9*m_timeToLiveSeconds*.1f));
		m_isDirty = true;
	}
}

void Light::render()
{
	if(m_shouldBeDisplayed)
	{
		DebugPoint::render();
	}
}

bool Light::shouldBeRemoved()
{
	return false;
}

//ASSUMES the correct buffer and shader program are already in place
/*void Light::sendLightsToOpenGL(unsigned int lightBufferID)
{
	//glUseProgram(programID);
	//TODO get the correct buffer from Renderer
	//it's also probably the same buffer that needs to be passed in for buffer subdata
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//unsigned int lightBuffer = glGetUniformBlockIndex(programID, "LightBlock");
	CompactLight lightData = CompactLight(*this);
	glBufferSubData(lightBufferID, m_blockOffset, sizeof(CompactLight), &lightData);
	//glUniformBlockBinding(programID, 0, lightBuffer);
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightBuffer);
}*/

CompactLight::CompactLight(Light lightToBeCompressed)
{
	values[0] = lightToBeCompressed.m_origin.x;
	values[1] = lightToBeCompressed.m_origin.y;
	values[2] = lightToBeCompressed.m_origin.z;
	values[3] = lightToBeCompressed.m_firstColor.red;
	values[4] = lightToBeCompressed.m_firstColor.green;
	values[5] = lightToBeCompressed.m_firstColor.blue;
	values[6] = lightToBeCompressed.m_firstColor.alphaValue;
	values[7] = lightToBeCompressed.m_direction.x;
	values[8] = lightToBeCompressed.m_direction.y;
	values[9] = lightToBeCompressed.m_direction.z;
	values[10] = lightToBeCompressed.m_innerRadius;
	values[11] = lightToBeCompressed.m_outerRadius;
	values[12] = lightToBeCompressed.m_innerApertureDot;
	values[13] = lightToBeCompressed.m_outerApertureDot;
	values[14] = lightToBeCompressed.m_fractionAmbient;
}