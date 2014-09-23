#pragma once
#ifndef include_EVENTSUBSCRIBERINTERFACE
#define include_EVENTSUBSCRIBERINTERFACE

#include "NamedProperties.hpp"

class EventSubscriberInterface
{
public:
	EventSubscriberInterface(){}

	virtual bool defaultEventCallback(const NamedProperties& arguments) = 0;
};


#endif