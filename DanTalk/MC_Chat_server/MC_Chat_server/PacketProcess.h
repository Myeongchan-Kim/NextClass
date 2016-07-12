#pragma once

#include "Packet.h"
#include "ITcpNetwork.h"
#include "ILog.h"
#include "Common.h"

using ERROR_CODE = Common::ERROR_CODE;
class ITcpNetwork;
class ILog;

class UserManager;
class LobbyManager;

#define CHECK_START  ERROR_CODE __result=ERROR_CODE::NONE;
#define CHECK_ERROR(f) __result=f; goto CHECK_ERR;

class PacketProcess
{
	using PacketInfo = Packet::RecvPacketInfo;
	typedef ERROR_CODE(PacketProcess::*PacketFunc)(PacketInfo);
	PacketFunc PacketFuncArray[(int)Common::PACKET_ID::MAX];

	using TcpNet = ITcpNetwork;
	
public:
	PacketProcess() {};
	~PacketProcess() {};

	void Init(TcpNet* pNetwork, UserManager* pUserMgr, LobbyManager* pLobbyMgr, ILog* pLogger);

	void Process(PacketInfo packetInfo);

	void StateCheck();
private:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;
	UserManager* m_pRefUserMgr;
	LobbyManager* m_pRefLobbyMgr;


private:
	ERROR_CODE NtfSysCloseSesson(PacketInfo packetInfo);
	ERROR_CODE Login(PacketInfo packetInfo);
	ERROR_CODE Logout(PacketInfo packetInfo);
	ERROR_CODE LobbyList(PacketInfo packetInfo);
	ERROR_CODE LobbyEnter(PacketInfo packetInfo);
	ERROR_CODE LobbyRoomList(PacketInfo packetInfo);
	ERROR_CODE LobbyUserList(PacketInfo packetInfo);
	ERROR_CODE LobbyLeave(PacketInfo packetInfo);
	ERROR_CODE RoomEnter(PacketInfo packetInfo);
	ERROR_CODE RoomUserList(PacketInfo packetInfo);
	ERROR_CODE RoomLeave(PacketInfo packetInfo);
	ERROR_CODE RoomChat(PacketInfo packetInfo);
	ERROR_CODE LobbyChat(PacketInfo packetInfo);
	ERROR_CODE LobbyWhisper(PacketInfo packetInfo);

	ERROR_CODE LeaveAllAndLogout(User* pUser, int SessionId);
};