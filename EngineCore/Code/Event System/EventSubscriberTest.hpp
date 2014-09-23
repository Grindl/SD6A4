#pragma once

#include "EventSubscriberInterface.hpp"

//TODO to be consistent, this should probably be DebugEventSubscriber
class EventSubscriberTest : public EventSubscriberInterface
{
public:
	EventSubscriberTest()
	{

	}

	virtual bool defaultEventCallback(const NamedProperties& arguments)
	{
		int charlieReached = 1;
		return true;
	}
};