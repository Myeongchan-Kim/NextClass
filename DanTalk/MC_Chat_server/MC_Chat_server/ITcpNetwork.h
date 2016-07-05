#pragma once

#include "ServerConfig.h"
#include "Packet.h"
class ILog;

using NET_ERROR_CODE = ServerConfig::NET_ERROR_CODE;

class ITcpNetwork
{
public:
	ITcpNetwork() {}
	virtual ~ITcpNetwork() {}

	virtual NET_ERROR_CODE Init(const ServerConfig* pConfig, ILog* pLogger) { return NET_ERROR_CODE::NONE; }

	virtual NET_ERROR_CODE SendData(const int sessionIndex, const short packetId,
		const short size, const char* pMsg) {
		return NET_ERROR_CODE::NONE;
	}

	virtual void Run() {}

	virtual Packet::RecvPacketInfo GetPacketInfo() { return Packet::RecvPacketInfo(); }
};