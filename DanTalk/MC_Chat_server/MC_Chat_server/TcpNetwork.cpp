#include <stdio.h>
#include <vector>
#include <deque>

#include "Common.h"
#include "ILog.h"
#include "TcpNetwork.h"

using PACKET_ID = Common::PACKET_ID;

TcpNetwork::~TcpNetwork()
{
	for (auto& client : m_ClientSessionPool)
	{
		if (client.pRecvBuffer)
			delete[] client.pRecvBuffer;

		if (client.pSendBuffer)
			delete[] client.pSendBuffer;
	}
}

NET_ERROR_CODE TcpNetwork::Init(const ServerConfig * pConfig, ILog * pLogger)
{
	memcpy(&m_Config, pConfig, sizeof(ServerConfig));
	m_pRefLogger = pLogger;

	auto initRet = InitServerSocket();
	if (initRet != NET_ERROR_CODE::NONE)
		return initRet;

	auto bindListenRet = BindListen(pConfig->Port, pConfig->BackLogCount);
	if (bindListenRet != NET_ERROR_CODE::NONE)
		return bindListenRet;

	FD_ZERO(&m_Readfds);
	FD_SET(m_ServerSockfd, &m_Readfds);

	CreateSessionPool(pConfig->MaxClientCount + pConfig->ExtraClientCount);

	return NET_ERROR_CODE::NONE;
}

void TcpNetwork::Run()
{
	auto read_set = m_Readfds;
	auto write_set = m_Readfds;
	auto excut_set = m_Readfds;

	timeval timeout{ 0, 1000 }; // tv_sec, tv_usec
	auto selectResult = select(0, &read_set, &write_set, &excut_set, &timeout);

	auto isFDSetChanged = RunCheckSelectResult(selectResult);
	if (isFDSetChanged == false)
		return;

	//accept . ���� ���Ѱ� ������.
	if (FD_ISSET(m_ServerSockfd, &read_set))
	{
		NewSession();
	}
	else // clients
	{
		RunCheckSelectClients(excut_set, read_set, write_set);
	}
}

Packet::RecvPacketInfo TcpNetwork::GetPacketInfo()
{
	Packet::RecvPacketInfo packetInfo;

	if (m_PacketQueue.empty() == false)
	{
		packetInfo = m_PacketQueue.front();
		m_PacketQueue.pop_front();
	}

	return packetInfo;
}

NET_ERROR_CODE TcpNetwork::InitServerSocket()
{
	WORD mVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(mVersionRequested, &wsaData);

	m_ServerSockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ServerSockfd < 0)
		return NET_ERROR_CODE::SERVER_SOCKET_CREATE_FAIL;

	auto n = 1;
	if (setsockopt(m_ServerSockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&n, sizeof(n)) < 0)
		return NET_ERROR_CODE::SERVER_SOCKET_SO_REUSEADDR_FAIL;

	return NET_ERROR_CODE::NONE;
}

NET_ERROR_CODE TcpNetwork::BindListen(short port, int backlogCount)
{
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(SOCKADDR_IN));
	server_addr.sin_addr.s_addr = htonl(ADDR_ANY);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if (bind(m_ServerSockfd, (SOCKADDR*)&server_addr, sizeof(server_addr)))
		return NET_ERROR_CODE::SERVER_SOCKET_BIND_FAIL;
	if (listen(m_ServerSockfd, backlogCount) == SOCKET_ERROR)
		return NET_ERROR_CODE::SERVER_SOCKET_LISTEN_FAIL;

	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | Listen. ServerSockfd(%d)", __FUNCTION__, m_ServerSockfd);

	return NET_ERROR_CODE::NONE;
}

int TcpNetwork::AllocClientSessionIndex()
{
	if (m_ClientSessionPoolIndex.empty())
		return -1;

	int index = m_ClientSessionPoolIndex.front();
	m_ClientSessionPoolIndex.pop_front();

	return index;
}

void TcpNetwork::CreateSessionPool(const int maxClientCount)
{
	for (int i = 0; i < maxClientCount; i++)
	{
		ServerConfig::ClientSession session;
		ZeroMemory(&session, sizeof(ServerConfig::ClientSession));
		session.Index = i;
		session.pRecvBuffer = new char[m_Config.MaxClientRecvBufferSize];
		session.pSendBuffer = new char[m_Config.MaxClientSendBufferSize];

		m_ClientSessionPool.push_back(session);
		m_ClientSessionPoolIndex.push_back(session.Index);
	}
}

NET_ERROR_CODE TcpNetwork::NewSession()
{
	SOCKADDR_IN client_addr;
	int client_len = static_cast<int>(sizeof(client_addr));
	auto client_sockfd = accept(m_ServerSockfd, (SOCKADDR*)&client_addr, &client_len);

	if (client_sockfd < 0)
	{
		m_pRefLogger->Write(LOG_TYPE::L_ERROR, "%s | Wrong socket %d cannot accept", __FUNCTION__, client_sockfd);
		return NET_ERROR_CODE::ACCEPT_API_ERROR;
	}

	auto newSessionIndex = AllocClientSessionIndex(); //index pool �̿��ؼ� ������ �ִ��� üũ.
	if (newSessionIndex < 0)
	{
		m_pRefLogger->Write(LOG_TYPE::L_WARN, "%s | client_sockfd(%d) >= MAX_SESSION", __FUNCTION__, client_sockfd);
		//pool���� ��� �� �� �������Ƿ� �ٷ� ¥��. 
		CloseSession(ServerConfig::SOCKET_CLOSE_CASE::SESSION_POOL_EMPTY, client_sockfd, -1);
		return NET_ERROR_CODE::ACCEPT_MAX_SESSION_COUNT;
	}

	char clientIP[ServerConfig::MAX_IP_LEN] = { 0, };
	inet_ntop(AF_INET, &(client_addr.sin_addr), clientIP, ServerConfig::MAX_IP_LEN - 1);

	SetSockOption(client_sockfd);
	FD_SET(client_sockfd, &m_Readfds);

	ConnectedSession(newSessionIndex, (int)client_sockfd, clientIP);//�������... ���� �̿ϼ�

	return NET_ERROR_CODE::NONE;
}

void TcpNetwork::SetSockOption(const SOCKET fd)
{
	linger ling{ 0, 0 };
	setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(ling));

	int recvSize = m_Config.MaxClientRecvBufferSize;
	int sendSize = m_Config.MaxClientSendBufferSize;
	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char*)&recvSize, sizeof(recvSize)); // �� �ּҸ� ������? �Ф� ���� ������ �Ǵ°� �ƴѰ�...
	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&sendSize, sizeof(sendSize));
}

void TcpNetwork::ConnectedSession(const int sessionIndex, const int fd, const char * pIP)
{
	++m_ConnectSeq;

	auto& newSession = m_ClientSessionPool[sessionIndex];
	newSession.Seq = m_ConnectSeq;
	newSession.SocketFD = fd;
	memcpy(newSession.IP, pIP, ServerConfig::MAX_IP_LEN - 1);

	++m_ConnectedSessionCount;

	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | New Session. FD(%d), m_ConnectSeq(%d), IP(%s)", __FUNCTION__, fd, m_ConnectSeq, pIP);
	return;
}

void TcpNetwork::CloseSession(const ServerConfig::SOCKET_CLOSE_CASE closeCase, const SOCKET sockFD, const int sessionIndex)
{
	if (closeCase == ServerConfig::SOCKET_CLOSE_CASE::SESSION_POOL_EMPTY)
	{
		closesocket(sockFD);
		FD_CLR(sockFD, &m_Readfds);
		return;
	}

	if (m_ClientSessionPool[sessionIndex].IsConnected() == false)
	{
		return;
	}

	closesocket(sockFD);
	FD_CLR(sockFD, &m_Readfds);

	m_ClientSessionPool[sessionIndex].Clear();
	m_ClientSessionPoolIndex.push_back(sessionIndex);
	--m_ConnectedSessionCount;

	AddPacketQueue(sessionIndex, (short)PACKET_ID::NTF_SYS_CLOSE_SESSION, 0, nullptr);
}

NET_ERROR_CODE TcpNetwork::RecvSocket(const int sessionIndex)
{
	auto& session = m_ClientSessionPool[sessionIndex];
	auto fd = static_cast<SOCKET>(session.SocketFD);

	if (session.IsConnected() == false)
		return NET_ERROR_CODE::RECV_PROCESS_NOT_CONNECTED;

	int recvPos = 0;

	if (session.RemainingDataSize > 0)
	{
		memcpy(session.pRecvBuffer, &session.pRecvBuffer[m_BeforeReadPos], session.RemainingDataSize);
		m_BeforeReadPos = 0;

		recvPos += session.RemainingDataSize; // ���⼭ recvPos == remaining datasize �ƴѰ�?						
	}

	int recvSize = recv(fd, &session.pRecvBuffer[recvPos], (ServerConfig::MAX_PACKET_SIZE * 2), 0); //�� ��Ŷ ����� 2�� ���ϴ°��� �Ф�

	if (recvSize == 0)
		return NET_ERROR_CODE::RECV_REMOTE_CLOSE; //��� �����͸� �о graceful close�� ������ ��Ȳ?

	if (recvSize < 0)
	{
		auto err = WSAGetLastError();
		if (err != WSAEWOULDBLOCK) //WOULDBLOCK�� ���� �ٺ��� ���� ���� ���ϴ� ���̶�� ��. 
			return NET_ERROR_CODE::RECV_API_ERROR;
		else
			return NET_ERROR_CODE::NONE;
	}

	session.RemainingDataSize += recvSize;
	return NET_ERROR_CODE::NONE;
}

NET_ERROR_CODE TcpNetwork::RecvBufferProcess(const int sessionIndex)
{
	auto& session = m_ClientSessionPool[sessionIndex];
	auto readPos = 0;

	const auto dataSize = session.RemainingDataSize;
	Packet::PktHeader* pPktHeader;

	while ((dataSize - readPos) >= ServerConfig::PACKET_HEADER_SIZE)
	{
		pPktHeader = (Packet::PktHeader*)&session.pRecvBuffer[readPos];
		readPos += ServerConfig::PACKET_HEADER_SIZE;

		if (pPktHeader->BodySize > 0)
		{
			if (pPktHeader->BodySize > (dataSize - readPos))
			{
				readPos -= ServerConfig::PACKET_HEADER_SIZE;
				break;
			}
			if (pPktHeader->BodySize > ServerConfig::MAX_PACKET_SIZE)
			{
				break;
			}
		}
		AddPacketQueue(sessionIndex, pPktHeader->Id, pPktHeader->BodySize, &session.pRecvBuffer[readPos]);
		readPos += pPktHeader->BodySize;
	}
	session.RemainingDataSize -= readPos;
	m_BeforeReadPos = readPos;

	return NET_ERROR_CODE::NONE;
}

void TcpNetwork::AddPacketQueue(const int sessionIndex, const short pktId, const short bodySize, char * pDataPos)
{
	Packet::RecvPacketInfo packetInfo;
	packetInfo.SessionIndex = sessionIndex;
	packetInfo.PacketId = pktId;
	packetInfo.PacketBodySize = bodySize;
	packetInfo.pRefData = pDataPos;

	m_PacketQueue.push_back(packetInfo);
}

void TcpNetwork::RunProcessWrite(const int sessionIndex, const SOCKET fd, fd_set & write_set)
{
	auto retSend = FlushSendBuff(sessionIndex);
	if (retSend.Error != NET_ERROR_CODE::NONE)
		CloseSession(ServerConfig::SOCKET_CLOSE_CASE::SOCKET_SEND_ERROR, fd, sessionIndex);
}

ServerConfig::NetError TcpNetwork::FlushSendBuff(const int sessionIndex)
{
	auto& session = m_ClientSessionPool[sessionIndex];
	auto fd = static_cast<SOCKET>(session.SocketFD);

	if (session.IsConnected() == false)
	{
		return NET_ERROR_CODE::CLIENT_FLUSH_SEND_BUFF_REMOTE_CLOSE;
	}

	auto result = SendSocket(fd, session.pSendBuffer, session.SendSize);

	if (result.Error != NET_ERROR_CODE::NONE) {
		return result;
	}

	auto sendSize = result.Value;
	if (sendSize < session.SendSize)
	{
		memmove(&session.pSendBuffer[0], &session.pSendBuffer[sendSize], session.SendSize - sendSize);
		session.SendSize -= sendSize;
	}
	else
	{
		session.SendSize = 0;
	}
	return result;
}

ServerConfig::NetError TcpNetwork::SendSocket(const SOCKET fd, const char * pMsg, const int size)
{
	ServerConfig::NetError result(NET_ERROR_CODE::NONE);
	auto rfds = m_Readfds;

	if (size <= 0)
		return result;

	result.Value = send(fd, pMsg, size, 0);

	if (result.Value <= 0)
		result.Error = NET_ERROR_CODE::SEND_CLOSE_SOCKET;

	return result;
}

bool TcpNetwork::RunCheckSelectResult(const int result)
{
	if (result == 0)
		return false; //every socket is not changed.
	else if (result == -1)
	{
		m_pRefLogger->Write(LOG_TYPE::L_ERROR, "Select error.");
		return false;
	}

	return true;
}

void TcpNetwork::RunCheckSelectClients(fd_set & exc_set, fd_set & read_set, fd_set & write_set)
{
	for (int i = 0; i < m_ClientSessionPool.size(); i++)
	{
		auto& session = m_ClientSessionPool[i];

		if (session.IsConnected() == false)
			continue;

		auto fd = session.SocketFD;
		auto sessionIndex = session.Index;

		//error check
		if (FD_ISSET(fd, &exc_set))
		{
			CloseSession(ServerConfig::SOCKET_CLOSE_CASE::SELECT_ERROR, fd, sessionIndex);
			continue;
		}

		//read check
		auto retRecieve = RunProcessReceive(sessionIndex, fd, read_set);
		if (retRecieve == false) //���� ���� �����Ͱ� ���ٸ� write ������ ���� ����. 
			continue;

		//write check
		if (!FD_ISSET(fd, &write_set))
			continue;
		RunProcessWrite(sessionIndex, fd, write_set);
	}
}

bool TcpNetwork::RunProcessReceive(const int sessionIndex, const SOCKET fd, fd_set & read_set)
{
	if (!FD_ISSET(fd, &read_set))
		return true;

	//���Ͽ� ���� �����͸� ����.
	auto ret = RecvSocket(sessionIndex);
	if (ret != NET_ERROR_CODE::NONE)
	{
		CloseSession(ServerConfig::SOCKET_CLOSE_CASE::SOCKET_RECV_ERROR, fd, sessionIndex);
		return false;
	}

	//��Ŷ������ �����͸� ����.????
	ret = RecvBufferProcess(sessionIndex);
	if (ret != NET_ERROR_CODE::NONE)
	{
		CloseSession(ServerConfig::SOCKET_CLOSE_CASE::SOCKET_RECV_ERROR, fd, sessionIndex);
		return false;
	}

	return true;
}

ServerConfig::NET_ERROR_CODE TcpNetwork::SendData(const int sessionIndex, const short packetId, const short size, const char* pMsg)
{
	auto& session = m_ClientSessionPool[sessionIndex];

	auto pos = session.SendSize;

	if ((pos + size + ServerConfig::PACKET_HEADER_SIZE) > m_Config.MaxClientSendBufferSize) {
		return NET_ERROR_CODE::CLIENT_SEND_BUFFER_FULL;
	}

	Packet::PktHeader pktHeader{ packetId, size };
	memcpy(&session.pSendBuffer[pos], (char*)&pktHeader, ServerConfig::PACKET_HEADER_SIZE);
	memcpy(&session.pSendBuffer[pos + ServerConfig::PACKET_HEADER_SIZE], pMsg, size);
	session.SendSize += (size + ServerConfig::PACKET_HEADER_SIZE);

	return NET_ERROR_CODE::NONE;

}