#pragma once
#ifndef include_ELEMENT
#define include_ELEMENT

class Element
{
public:
	Element();

	bool m_shouldBeRemoved;

	virtual void update(float deltaSeconds) = 0;
	virtual void render() = 0;
	virtual bool shouldBeRemoved() {return m_shouldBeRemoved;}
};


#endif