#include "EventSystemHandler.hpp"

#include "Memory Manager/MemoryManager.hpp"

//-----------------------------------------------------------------------------
EventSystemHandler::EventSystemHandler()
{

}

//-----------------------------------------------------------------------------
void EventSystemHandler::addSubscriber(std::string eventName, EventSubscriberNode* callbackObject)
{
	m_eventSubscriberRegistry[eventName].push_back(callbackObject);
}

//-----------------------------------------------------------------------------
void EventSystemHandler::removeSubscriber(std::string eventName, EventSubscriberNode* callbackObject)
{
	//TODO
}

//-----------------------------------------------------------------------------
void EventSystemHandler::fireEvent(const std::string eventName, const NamedProperties& parameters)
{
	if(m_eventSubscriberRegistry.find(eventName) != m_eventSubscriberRegistry.end())
	{
		for(int ii = 0; ii < m_eventSubscriberRegistry[eventName].size(); ii++)
		{
			m_eventSubscriberRegistry[eventName][ii]->fireCallbackFunctions(parameters);
		}
	}
}