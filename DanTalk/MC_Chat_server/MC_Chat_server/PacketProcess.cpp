#include "Common.h"
#include "ILog.h"
#include "TcpNetwork.h"
#include "User.h"
#include "UserManager.h"
#include "Room.h"
#include "Lobby.h"
#include "LobbyManager.h"
#include "PacketProcess.h"

using PACKET_ID = Common::PACKET_ID;

void PacketProcess::Init(TcpNet* pNetwork, UserManager* pUserMgr, LobbyManager* pLobbyMgr, ILog* pLogger)
{
	m_pRefLogger = pLogger;
	m_pRefNetwork = pNetwork;
	m_pRefUserMgr = pUserMgr;
	m_pRefLobbyMgr = pLobbyMgr;

	for (int i = 0; i < (int)PACKET_ID::MAX; ++i)
	{
		PacketFuncArray[i] = nullptr;
	}

	PacketFuncArray[(int)PACKET_ID::NTF_SYS_CLOSE_SESSION] = &PacketProcess::NtfSysCloseSesson;
	PacketFuncArray[(int)PACKET_ID::LOGIN_IN_REQ] = &PacketProcess::Login;
	PacketFuncArray[(int)PACKET_ID::LOBBY_LIST_REQ] = &PacketProcess::LobbyList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_REQ] = &PacketProcess::LobbyEnter;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ] = &PacketProcess::LobbyRoomList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_USER_LIST_REQ] = &PacketProcess::LobbyUserList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_LEAVE_REQ] = &PacketProcess::LobbyLeave;
	//PacketFuncArray[(int)PACKET_ID::ROOM_ENTER_REQ] = &PacketProcess::RoomEnter;
	//PacketFuncArray[(int)PACKET_ID::ROOM_LEAVE_REQ] = &PacketProcess::RoomLeave;
	//PacketFuncArray[(int)PACKET_ID::ROOM_CHAT_REQ] = &PacketProcess::RoomChat;
}

void PacketProcess::Process(PacketInfo packetInfo)
{
	auto packetId = packetInfo.PacketId;

	if (PacketFuncArray[packetId] == nullptr)
	{
		//TODO: 로그 남긴다
	}

	(this->*PacketFuncArray[packetId])(packetInfo);
}

ERROR_CODE PacketProcess::NtfSysCloseSesson(PacketInfo packetInfo)
{
	auto pUser = std::get<1>(m_pRefUserMgr->GetUser(packetInfo.SessionIndex));

	if (pUser)
	{
		auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
		if (pLobby)
		{
			auto pRoom = pLobby->GetRoom(pUser->GetRoomIndex());

			if (pRoom)
			{
				pRoom->LeaveUser(pUser->GetIndex());
				pRoom->NotifyLeaveUserInfo(pUser->GetID().c_str());
				pLobby->NotifyChangedRoomInfo(pRoom->GetIndex());

				m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d). Room Out", __FUNCTION__, packetInfo.SessionIndex);
			}

			pLobby->LeaveUser(pUser->GetIndex());

			if (pRoom == nullptr) {
				pLobby->NotifyLobbyLeaveUserInfo(pUser);
			}

			m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d). Lobby Out", __FUNCTION__, packetInfo.SessionIndex);
		}

		m_pRefUserMgr->RemoveUser(packetInfo.SessionIndex);
	}


	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d)", __FUNCTION__, packetInfo.SessionIndex);
	return ERROR_CODE::NONE;
}

/***********************/
/****** ON LOGIN  ******/
/***********************/
ERROR_CODE PacketProcess::Login(PacketInfo packetInfo)
{
	CHECK_START;
	//(Todo) 받은 데이터가 PktLoginReq 크기인지 확인.
	Packet::PktLogInRes resPkt;
	auto reqPkt = (Packet::PktLogInReq*)packetInfo.pRefData;

	// 이 안에서 중복 데이타 검사. 패스워드는 일단 무조건 맞는걸로...AddUser 안에서 ID 중복만 검사함.																					 
	auto addRet = m_pRefUserMgr->AddUser(packetInfo.SessionIndex, reqPkt->szID);

	if (addRet != ERROR_CODE::NONE)
	{
		CHECK_ERROR(addRet);
	}

	resPkt.ErrorCode = (short)addRet;
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOGIN_IN_RES,
		sizeof(Packet::PktLogInRes),
		(char*)&resPkt
	);

	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOGIN_IN_RES,
		sizeof(Packet::PktLogInRes),
		(char*)&resPkt
	);
	return (ERROR_CODE)__result;
}

ERROR_CODE PacketProcess::LobbyList(PacketInfo packetInfo)
{
	CHECK_START;
	//상태체크 : 로그인 상태?
	//응답 : 로비 리스트

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);
	if (errorCode != ERROR_CODE::NONE)
	{
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainLogin() == false)
	{
		CHECK_ERROR(ERROR_CODE::LOBBY_LIST_INVALID_DOMAIN);
	}
	m_pRefLobbyMgr->SendLobbyListInfo(packetInfo.SessionIndex);

	return ERROR_CODE::NONE;
CHECK_ERR:
	Packet::PktLobbyListRes resPkt;
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOBBY_LIST_RES,
		sizeof(Packet::PktLobbyListRes),
		(char*)&resPkt
	); //여기 원본 변수명이 좀 이상함!

	//m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | res Lobbylist. ", __FUNCTION__);

	return (ERROR_CODE)__result;
}


/***********************/
/***** ON  LOBBY  ******/
/***********************/
ERROR_CODE PacketProcess::LobbyEnter(PacketInfo packetInfo)
{
	CHECK_START;
	// 상태체크 : 로그인 
	// 몇번 로비에 들어갔는지 알려줌.
	// 로비에 있는 사람들에게 새 사람이 들어왔다고 알려줌. 
	Packet::PktLobbyEnterReq* reqPkt = (Packet::PktLobbyEnterReq*)packetInfo.pRefData;
	Packet::PktLobbyEnterRes  resPkt;

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);
	auto pUser = std::get<1>(pUserRet);

	if (errorCode != ERROR_CODE::NONE)
	{
		CHECK_ERROR(errorCode);
	}

	if (pUser->IsCurDomainLogin() == false)
	{
		return ERROR_CODE::LOBBY_ENTER_INVALID_DOMAIN;
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(reqPkt->LobbyId);
	if (pLobby == nullptr)
	{
		CHECK_ERROR(ERROR_CODE::LOBBY_ENTER_INVALID_LOBBY_INDEX);
	}

	auto enterRet = pLobby->EnterUser(pUser);
	if (enterRet != ERROR_CODE::NONE)
	{
		CHECK_ERROR(enterRet); // 아마도 꽉차서?
	}

	pLobby->NotifyLobbyEnterUserInfo(pUser);

	resPkt.MaxUserCount = pLobby->MaxRoomCount();
	resPkt.MaxRoomCount = pLobby->MaxRoomCount();
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_ENTER_RES, sizeof(Packet::PktLobbyEnterRes), (char*)&resPkt);

	return ERROR_CODE::NONE;
CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_ENTER_RES, sizeof(Packet::PktLobbyEnterRes), (char*)&resPkt);
	return (ERROR_CODE)__result;
}


ERROR_CODE PacketProcess::LobbyRoomList(PacketInfo packetInfo)
{
	CHECK_START;
	//상태체크 : 로비에 있는가?
	//응답 : 룸 리스트 보내줌.

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);
	auto pUser = std::get<1>(pUserRet);

	if (errorCode != ERROR_CODE::NONE)
	{
		CHECK_ERROR(errorCode);
	}
	if (pUser->IsCurDomainLobby() == false)
	{
		CHECK_ERROR(ERROR_CODE::LOBBY_LIST_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr)
	{
		CHECK_ERROR(ERROR_CODE::LOBBY_ROOM_LIST_INVALID_LOBBY_INDEX);
	}

	auto reqPkt = (Packet::PktLobbyRoomListReq*)packetInfo.pRefData;
	pLobby->SendRoomList(pUser->GetSessionIndex(), reqPkt->StartRoomIndex);

	return ERROR_CODE::NONE;

CHECK_ERR:
	Packet::PktLobbyRoomListRes resPkt;
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOBBY_ENTER_ROOM_LIST_RES,
		sizeof(Packet::PktLobbyRoomListRes), //여기도 원본이 PktBase로 되어있었담.
		(char*)&resPkt
	);
	return (ERROR_CODE)__result;
}


ERROR_CODE PacketProcess::LobbyUserList(PacketInfo packetInfo)
{
CHECK_START
	// 현재 로비에 있는지 조사한다.
	// 유저 리스트를 보내준다.

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::LOBBY_USER_LIST_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr) {
		CHECK_ERROR(ERROR_CODE::LOBBY_USER_LIST_INVALID_LOBBY_INDEX);
	}

	auto reqPkt = (Packet::PktLobbyUserListReq*)packetInfo.pRefData;

	pLobby->SendUserList(pUser->GetSessionIndex(), reqPkt->StartUserIndex);

	return ERROR_CODE::NONE;
CHECK_ERR:
	Packet::PktLobbyUserListRes resPkt;
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_ENTER_USER_LIST_RES, sizeof(Packet::PktBase), (char*)&resPkt);
	return (ERROR_CODE)__result;
}


ERROR_CODE PacketProcess::LobbyLeave(PacketInfo packetInfo)
{
CHECK_START
	// 현재 로비에 있는지 조사한다.
	// 로비에서 나간다
	// 기존 로비에 있는 사람에게 나가는 사람이 있다고 알려준다.
	Packet::PktLobbyLeaveRes resPkt;

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::LOBBY_LEAVE_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr) {
		CHECK_ERROR(ERROR_CODE::LOBBY_LEAVE_INVALID_LOBBY_INDEX);
	}

	auto enterRet = pLobby->LeaveUser(pUser->GetIndex());
	if (enterRet != ERROR_CODE::NONE) {
		CHECK_ERROR(enterRet);
	}

	pLobby->NotifyLobbyLeaveUserInfo(pUser);
			
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_LEAVE_RES, sizeof(Packet::PktLobbyLeaveRes), (char*)&resPkt);

	return ERROR_CODE::NONE;
CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_LEAVE_RES, sizeof(Packet::PktLobbyLeaveRes), (char*)&resPkt);
	return (ERROR_CODE)__result;
}
