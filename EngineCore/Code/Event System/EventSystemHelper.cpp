#include "EventSystemHelper.hpp"
#include "EventSubscriberTest.hpp"

#include "Memory Manager/MemoryManager.hpp"

EventSystemHandler g_universalEventSystem = EventSystemHandler();



//-----------------------------------------------------------------------------
void registerEventSubscriberGlobal(std::string eventName, EventSubscriberNode* callbackObject)
{
	g_universalEventSystem.addSubscriber(eventName, callbackObject);
}

//-----------------------------------------------------------------------------
void unregisterEventSubscriberGlobal(std::string eventName, EventSubscriberNode* callbackObject)
{
	g_universalEventSystem.removeSubscriber(eventName, callbackObject);
}

//-----------------------------------------------------------------------------
void fireEventGlobal(std::string eventName)
{
	//TODO
}

//-----------------------------------------------------------------------------
void fireEventGlobal(const std::string eventName, const NamedProperties& params)
{
	g_universalEventSystem.fireEvent(eventName, params);
}

//class orc : public EventSubscriberInterface

//-----------------------------------------------------------------------------
void unitTestEventSystem()
{
	EventSubscriberNode* alphaNode = new EventSubscriberNode();
	EventSubscriberNode* bravoNode = new EventSubscriberNode();
	EventSubscriberNode* charlieNode = new EventSubscriberNode();

	alphaNode->setStaticCallbackFunction(thisIsAlpha);
	bravoNode->setStaticCallbackFunction(thisIsBravo);
	EventSubscriberTest* charlieObject = new EventSubscriberTest();
	charlieNode->setMemberCallbackFunction(charlieObject, &EventSubscriberInterface::defaultEventCallback);

	registerEventSubscriberGlobal("Sunrise", alphaNode);
	registerEventSubscriberGlobal("Sunrise", charlieNode);
	registerEventSubscriberGlobal("Sunset", alphaNode);

	NamedProperties genericProperties = NamedProperties();
	NamedProperties::NamedHelper<float>* genericValue = new NamedProperties::NamedHelper<float>();
	float genericFloat = 1.f;
	genericValue->val = &genericFloat;
	genericProperties.addProperty("Brightness", genericValue);

	fireEventGlobal("Sunrise", genericProperties);
	fireEventGlobal("Sunset", genericProperties);
	fireEventGlobal("Noon", genericProperties);
}

//-----------------------------------------------------------------------------
bool thisIsAlpha(const NamedProperties& params)
{
	int alphaCallback = 0;
	return true;
}
//-----------------------------------------------------------------------------
bool thisIsBravo(const NamedProperties& params)
{
	int bravoCallback = 0;
	return true;
}