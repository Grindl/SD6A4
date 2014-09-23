#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Connection.hpp"

Connection::Connection(const char* IPAddress, const char* port)
{
	WSAData myWSAData;
	int WSAResult;
	m_Socket = INVALID_SOCKET;

	long IPAsLong = inet_addr(IPAddress);
	u_long fionbioFlag = 1;

	m_SockAddr.sin_family = AF_INET;
	m_SockAddr.sin_port = htons(atoi(port));
	m_SockAddr.sin_addr.S_un.S_addr = IPAsLong;

	srand(time(0));

	struct sockaddr_in outboundAddress;
	outboundAddress.sin_family = AF_INET;
	outboundAddress.sin_port = 50000+(rand()%1000); //randomly assigned address with minimal collision
	outboundAddress.sin_addr.S_un.S_addr = INADDR_ANY;
	

	WSAResult = WSAStartup(MAKEWORD(2,2), &myWSAData);
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	WSAResult = ioctlsocket(m_Socket, FIONBIO, &fionbioFlag);
	WSAResult = bind(m_Socket, (const sockaddr*)&outboundAddress, sizeof(outboundAddress));
}

Connection::~Connection()
{
	closesocket(m_Socket);
	WSACleanup();
}

bool Connection::sendPacket(CS6Packet pk)
{
	//set time and packet number, and increment number
	//then send
	int result = sendto(m_Socket, (char*)&pk, sizeof(pk), 0, (const sockaddr*)&m_SockAddr, sizeof(m_SockAddr));
	bool success = result != -1;
	return success;
}

CS6Packet Connection::receivePackets()
{
	struct sockaddr_in recvTarget;
	CS6Packet currentData;
	currentData.packetType = 0;
	int fromLength = sizeof(recvTarget);
	int errorCode;

	errorCode = recvfrom(m_Socket, (char*)&currentData, sizeof(CS6Packet), 0, (sockaddr*)&recvTarget, &fromLength);
	if (currentData.packetType != 0)
	{
		int BREAKSUCCESS = 0;
	}
	else
	{
		int newError = WSAGetLastError();
		int BREAKFAIL = 0;
	}
	return currentData;
}