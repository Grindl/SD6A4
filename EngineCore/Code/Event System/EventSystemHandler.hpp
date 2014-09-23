#pragma once
#ifndef include_EVENTSYSTEMHANDLER
#define include_EVENTSYSTEMHANDLER

#include <string>
#include <vector>
#include <map>

#include "EventBroadcastNode.hpp"
#include "EventSubscriberNode.hpp"
#include "NamedProperties.hpp"

class EventSystemHandler
{
public:
	EventSystemHandler();

	std::map<std::string, std::vector<EventSubscriberNode*> > m_eventSubscriberRegistry;
	
	void addSubscriber(std::string eventName, EventSubscriberNode* callbackObject);
	void removeSubscriber(std::string eventName, EventSubscriberNode* callbackObject);
	void fireEvent(const std::string eventName, const NamedProperties& parameters);
};


#endif