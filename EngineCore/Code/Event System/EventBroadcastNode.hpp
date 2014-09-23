#pragma once
#ifndef include_EVENTBROADCASTNODE
#define include_EVENTBROADCASTNODE


#include <string>
#include <vector>

class EventBroadcastNode
{
public:
	EventBroadcastNode();

	std::vector<std::string> m_eventNameToBroadcast;
};


#endif