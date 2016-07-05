#pragma once

#define FD_SETSIZE 1024 // http://blog.naver.com/znfgkro1/220175848048

#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <ws2tcpip.h>

#include <vector>
#include <deque>
#include <unordered_map>
#include "ITcpNetwork.h"
#include "ServerConfig.h"
#include "Packet.h"

class TcpNetwork : public ITcpNetwork
{
public:
	TcpNetwork() {};
	virtual ~TcpNetwork();

	NET_ERROR_CODE Init(const ServerConfig* pConfig, ILog* pLogger) override;
	NET_ERROR_CODE SendData(const int sessionIndex, const short packetId, const short size, const char* pMsg) override;
	void Run() override;
	Packet::RecvPacketInfo GetPacketInfo() override;


protected:
	NET_ERROR_CODE InitServerSocket();
	NET_ERROR_CODE BindListen(short port, int backlogCount);

	int AllocClientSessionIndex();

	void CreateSessionPool(const int maxClientCount);
	NET_ERROR_CODE NewSession();
	void SetSockOption(const SOCKET fd);
	void ConnectedSession(const int sessionIndex, const int fd, const char* pIP);

	void CloseSession(const ServerConfig::SOCKET_CLOSE_CASE closeCase, const SOCKET sockFD, const int sessionIndex);

	NET_ERROR_CODE RecvSocket(const int sessionIndex);
	NET_ERROR_CODE RecvBufferProcess(const int sessionIndex);
	void AddPacketQueue(const int sessionIndex, const short pktId, const short bodySize, char* pDataPos);

	void RunProcessWrite(const int sessionIndex, const SOCKET fd, fd_set& write_set);
	ServerConfig::NetError FlushSendBuff(const int sessionIndex);
	ServerConfig::NetError SendSocket(const SOCKET fd, const char* pMsg, const int size);

	bool RunCheckSelectResult(const int result);
	void RunCheckSelectClients(fd_set& exc_set, fd_set& read_set, fd_set& write_set);
	bool RunProcessReceive(const int sessionIndex, const SOCKET fd, fd_set& read_set);

protected:
	ServerConfig m_Config;

	SOCKET m_ServerSockfd;

	fd_set m_Readfds;
	size_t m_ConnectedSessionCount = 0;

	int64_t m_ConnectSeq = 0;
	int m_BeforeReadPos = 0;

	std::vector<ServerConfig::ClientSession> m_ClientSessionPool;
	std::deque<int> m_ClientSessionPoolIndex;

	std::deque<Packet::RecvPacketInfo> m_PacketQueue;

	ILog* m_pRefLogger;
};
