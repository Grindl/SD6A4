#pragma once
#ifndef include_CONNECTION
#define include_CONNECTION

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <vector>
#include "User.hpp"


#pragma comment(lib, "Ws2_32.lib")

class Connection
{
public:
	Connection(const char* IPAddress, const char* port);
	~Connection();

	struct sockaddr_in m_SockAddr;
	SOCKET m_Socket;

	bool sendPacket(CS6Packet pk);
	CS6Packet receivePackets();
};

extern Connection* g_serverConnection;


#endif