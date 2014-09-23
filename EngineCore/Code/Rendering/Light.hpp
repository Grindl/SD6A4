#pragma once
#ifndef include_LIGHT
#define include_LIGHT

#include "..\Debug Graphics\DebugPoint.hpp"

static const int SIZEOF_LIGHT = 15;
enum LIGHT_TYPE{INVALID_LIGHT = -1, GLOBAL_POINTLIGHT, LOCAL_POINTLIGHT, LOCAL_SPOTLIGHT, GLOBAL_SPOTLIGHT, 
	LOCAL_AMBIENTLIGHT, GLOBAL_AMBIENTLIGHT, GLOBAL_DIRECTIONALLIGHT};

class Light : public DebugPoint
{
public:
	Light();
	Light(LIGHT_TYPE type);

	
	Vector3f m_direction;
	float m_innerRadius;
	float m_outerRadius;
	float m_innerApertureDot;
	float m_outerApertureDot;
	float m_fractionAmbient;

	bool m_shouldBeDisplayed;
	bool m_isDirty;
	int m_blockOffset;
	bool m_movingLight;

	virtual void update(float deltaSeconds);
	virtual void render();
	virtual bool shouldBeRemoved();
	//void sendLightsToOpenGL(unsigned int lightBufferID);
};


struct CompactLight
{
public:
	CompactLight(Light lightToBeCompressed);

	float values[SIZEOF_LIGHT];
};

#endif