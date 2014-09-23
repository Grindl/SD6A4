#pragma once
#ifndef include_EVENTSUBSCRIBERNODE
#define include_EVENTSUBSCRIBERNODE


#include <string>
#include <vector>
#include "NamedProperties.hpp"
#include "EventSubscriberInterface.hpp"

typedef bool (EventSubscriberInterface::*eventCallbackMemberFuncPointer)(const NamedProperties& arguments);
typedef bool (*eventCallbackStaticFuncPointer)(const NamedProperties& arguments);

class EventSubscriberNode
{
public:
	EventSubscriberNode();

	std::string m_eventNameToListenFor;
	EventSubscriberInterface* m_memberCallbackObject;
	eventCallbackMemberFuncPointer m_memberCallback; //Note: will execute all non-null callbacks for each object on event
	eventCallbackStaticFuncPointer m_staticCallback;

	void setMemberCallbackFunction(EventSubscriberInterface* newCallbackObject, eventCallbackMemberFuncPointer newCallbackFunction); //typical use will be "this" pointer for first arg
	void setStaticCallbackFunction(eventCallbackStaticFuncPointer newCallbackFunctuon);
	bool fireCallbackFunctions(const NamedProperties& arguments);
};


#endif