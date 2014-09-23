#pragma once
#ifndef include_EVENTSYSTEMHELPER
#define include_EVENTSYSTEMHELPER

#include <string>
#include "NamedProperties.hpp"
#include "EventSystemHandler.hpp"



//void registerEventBroadcaster();

void registerEventSubscriberGlobal(std::string eventName, EventSubscriberNode* callbackObject);
void unregisterEventSubscriberGlobal(std::string eventName, EventSubscriberNode* callbackObject);

void fireEventGlobal(std::string eventName);
void fireEventGlobal(std::string eventName, const NamedProperties& params);

void unitTestEventSystem();
bool thisIsAlpha(const NamedProperties& params);
bool thisIsBravo(const NamedProperties& params);


#endif