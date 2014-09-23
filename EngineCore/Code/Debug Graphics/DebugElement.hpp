#pragma once
#ifndef include_DEBUGELEMENT
#define include_DEBUGELEMENT

#include "..\Primitives\Vector3f.hpp"
#include "..\Primitives\Color4f.hpp"
#include "..\Rendering\Material.hpp"
#include "..\Primitives\Element.hpp"

class DebugElement : public Element
{
public:
	DebugElement();
	DebugElement(Vector3f source, Color4f firstColor, float displayForSeconds, bool depthTest);
	
	Vector3f m_origin;
	Color4f m_firstColor;
	float m_timeToLiveSeconds;
	bool m_killNextFrame;
	bool m_depthTest;
	int m_textureID; //Deprecated
	bool m_hasTexture; //Deprecated
	int m_shaderID; //Deprecated
	Material m_material;


	virtual void update(float deltaSeconds);
	virtual void render();
	virtual bool shouldBeRemoved();


};


#endif