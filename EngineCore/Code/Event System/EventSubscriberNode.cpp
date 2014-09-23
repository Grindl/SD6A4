#include "EventSubscriberNode.hpp"

#include "Memory Manager/MemoryManager.hpp"

//-----------------------------------------------------------------------------
EventSubscriberNode::EventSubscriberNode()
{
	m_eventNameToListenFor = "";
	m_memberCallback = 0; 
	m_staticCallback = 0;
	m_memberCallbackObject = 0;
}

//-----------------------------------------------------------------------------
void EventSubscriberNode::setMemberCallbackFunction(EventSubscriberInterface* newCallbackObject, eventCallbackMemberFuncPointer newCallbackFunction)
{
	m_memberCallbackObject = newCallbackObject;
	m_memberCallback = newCallbackFunction;
}

//-----------------------------------------------------------------------------
void EventSubscriberNode::setStaticCallbackFunction(eventCallbackStaticFuncPointer newCallbackFunctuon)
{
	m_staticCallback = newCallbackFunctuon;
}

//-----------------------------------------------------------------------------
bool EventSubscriberNode::fireCallbackFunctions(const NamedProperties& arguments)
{
	bool callbackResults = false;
	if(m_memberCallback != 0 && m_memberCallbackObject !=0)
	{
		callbackResults = (m_memberCallbackObject->*m_memberCallback)(arguments);
	}
	if (m_staticCallback != 0)
	{
		callbackResults = (m_staticCallback)(arguments);
	}
	return callbackResults;
}