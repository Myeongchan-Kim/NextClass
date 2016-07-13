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
	PacketFuncArray[(int)PACKET_ID::LOGIN_OUT_REQ] = &PacketProcess::Logout;
	PacketFuncArray[(int)PACKET_ID::LOBBY_LIST_REQ] = &PacketProcess::LobbyList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_REQ] = &PacketProcess::LobbyEnter;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ] = &PacketProcess::LobbyRoomList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_ENTER_USER_LIST_REQ] = &PacketProcess::LobbyUserList;
	PacketFuncArray[(int)PACKET_ID::LOBBY_LEAVE_REQ] = &PacketProcess::LobbyLeave;
	PacketFuncArray[(int)PACKET_ID::ROOM_ENTER_REQ] = &PacketProcess::RoomEnter;
	PacketFuncArray[(int)PACKET_ID::ROOM_ENTER_USER_LIST_REQ] = &PacketProcess::RoomUserList;
	PacketFuncArray[(int)PACKET_ID::ROOM_LEAVE_REQ] = &PacketProcess::RoomLeave;
	PacketFuncArray[(int)PACKET_ID::ROOM_CHAT_REQ] = &PacketProcess::RoomChat;
	PacketFuncArray[(int)PACKET_ID::LOBBY_CHAT_REQ] = &PacketProcess::LobbyChat;
	PacketFuncArray[(int)PACKET_ID::LOBBY_WHISPER_REQ] = &PacketProcess::LobbyWhisper;
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

void PacketProcess::StateCheck()
{
	//m_pConnectedUserManager->LoginCheck();
}

ERROR_CODE PacketProcess::NtfSysCloseSesson(PacketInfo packetInfo)
{
	auto pUser = std::get<1>(m_pRefUserMgr->GetUser(packetInfo.SessionIndex));

	LeaveAllAndLogout(pUser, packetInfo.SessionIndex);

	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d)", __FUNCTION__, packetInfo.SessionIndex);
	return ERROR_CODE::NONE;
}

ERROR_CODE PacketProcess::LeaveAllAndLogout(User* pUser, int sessionId)
{
	if (pUser == nullptr)
		return ERROR_CODE::NONE;

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby)
	{
		auto pRoom = pLobby->GetRoom(pUser->GetRoomIndex());

		if (pRoom)
		{
			pRoom->LeaveUser(pUser->GetIndex());
			pRoom->NotifyLeaveUserInfo(pUser->GetID().c_str());
			pLobby->NotifyChangedRoomInfo(pRoom->GetIndex());

			m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d). Room Out", __FUNCTION__, sessionId);
		}

		pLobby->LeaveUser(pUser->GetIndex());

		if (pRoom == nullptr) {
			pLobby->NotifyLobbyLeaveUserInfo(pUser);
		}

		m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d). Lobby Out", __FUNCTION__, sessionId);
	}

	auto result = m_pRefUserMgr->RemoveUser(sessionId);
	return result;
}


/****     ****/
/* log  out  */
/*******  ****/
ERROR_CODE PacketProcess::Logout(PacketInfo packetInfo)
{
	CHECK_START;
	Packet::PktLogOutRes resPkt;
	auto reqPkt = (Packet::PktLogOutReq*)packetInfo.pRefData;
					
	auto pUser = std::get<1>(m_pRefUserMgr->GetUser(packetInfo.SessionIndex));

	//방과 로비를 빠져나감 처리하고, 유저목록에서 제거.
	auto delRet = LeaveAllAndLogout(pUser, packetInfo.SessionIndex);
		
	if (delRet != ERROR_CODE::NONE)
	{
		CHECK_ERROR(delRet);
	}

	resPkt.ErrorCode = (short)delRet;
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOGIN_OUT_RES,
		sizeof(Packet::PktLogOutRes),
		(char*)&resPkt
	);

	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(
		packetInfo.SessionIndex,
		(short)PACKET_ID::LOGIN_OUT_RES,
		sizeof(Packet::PktLogOutRes),
		(char*)&resPkt
	);
	return (ERROR_CODE)__result;
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

ERROR_CODE PacketProcess::RoomEnter(PacketInfo packetInfo)
{
	CHECK_START
	// 현재 로비에 있는지 조사한다.
	// 룸에 들어간다
	// 룸에 있는 사람들에게 룸에 사람이 왔다고 알려준다. 
	// 기존 로비에 있는 사람에게 로비에서 사람이 나갔다고 알려준다. 
	Packet::PktRoomEnterRes resPkt;
	Packet::PktRoomEnterReq* reqPkt = (Packet::PktRoomEnterReq*)packetInfo.pRefData;

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);
	auto pUser = std::get<1>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}
	
	if (pUser->IsCurDomainLobby() == false)
	{
		CHECK_ERROR(ERROR_CODE::ROOM_ENTER_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr) 
	{
		CHECK_ERROR(ERROR_CODE::ROOM_ENTER_INVALID_LOBBY_INDEX);
	}

	Room* pRoom = nullptr;
	if (reqPkt->IsCreate == true)
	{
		for (int i = 0; i < pLobby->MaxRoomCount(); i++)
		{
			auto tmpRoom = pLobby->GetRoom(i);
			if (tmpRoom->IsUsed() == false)
			{
				pRoom = tmpRoom;
				break;
			}
		}
		if (pRoom == nullptr)
		{
			CHECK_ERROR(ERROR_CODE::ROOM_ENTER_CREATE_FAIL);
		}
		pRoom->CreateRoom(reqPkt->RoomTitle);
	}
	else
	{
		pRoom = pLobby->GetRoom(reqPkt->RoomIndex);
		if (pRoom == nullptr)
		{
			CHECK_ERROR(ERROR_CODE::ROOM_ENTER_INVALID_ROOM_INDEX);
		}
	}

	if (pRoom->IsUsed() == false)
	{
		CHECK_ERROR(ERROR_CODE::ROOM_ENTER_NOT_CREATED);
	}


	//방에 새로운 유저를 집어 넣음
	pLobby->LeaveUser(pUser->GetIndex());
	pUser->EnterRoom(pLobby->GetIndex(), pRoom->GetIndex());

	//유저가 로비를 떠났다고 알림.
	pLobby->NotifyLobbyLeaveUserInfo(pUser);

	//방에 새로운 유저 입장함을 알림.
	pRoom->NotifyEnterUserInfo(pUser->GetIndex(), pUser->GetID().c_str());

	//로비에게 방 정보 변경을 알림.
	pLobby->NotifyChangedRoomInfo(pRoom->GetIndex());
	
	resPkt.RoomInfo.RoomIndex = pRoom->GetIndex();
	resPkt.RoomInfo.RoomUserCount = pRoom->GetUserCount();
	memcpy(resPkt.RoomInfo.RoomTitle, pRoom->GetTitle(), sizeof(wchar_t)*(Packet::MAX_ROOM_TITLE_SIZE + 1));

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_ENTER_RES, sizeof(Packet::PktRoomEnterRes), (char*)&resPkt);

	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_ENTER_RES, sizeof(Packet::PktRoomEnterRes), (char*)&resPkt);
	return (ERROR_CODE)__result;
}

ERROR_CODE PacketProcess::RoomUserList(PacketInfo packetInfo)
{
	CHECK_START;
	Packet::PktEnterRoomUserInfoRes resPkt;
	
		// 현재 룸에 있는지 조사한다.
		// 유저 리스트를 보내준다.

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::ROOM_USER_LIST_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr) {
		CHECK_ERROR(ERROR_CODE::ROOM_USER_LIST_INVALID_LOBBY_INDEX);
	}

	auto pRoom = pLobby->GetRoom(pUser->GetRoomIndex());
	
	resPkt.UserCount = pRoom->GetUserCount();
	resPkt.RoomIndex = pRoom->GetIndex();
	for (int i = 0; i < resPkt.UserCount; i++)
	{
		strcpy(resPkt.UserInfo[i].UserID, pRoom->GetUserID(i).c_str());
	}
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_ENTER_USER_LIST_RES, sizeof(resPkt), (char*)&resPkt);

	return ERROR_CODE::NONE;
CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_ENTER_USER_LIST_RES, sizeof(resPkt), (char*)&resPkt);
	return (ERROR_CODE)__result;
}

ERROR_CODE PacketProcess::RoomLeave(PacketInfo packetInfo)
{
	CHECK_START;
		// 현재 로비에 있는지 조사한다.
		// 로비에서 나간다
		// 기존 로비에 있는 사람에게 나가는 사람이 있다고 알려준다.
	Packet::PktRoomLeaveRes resPkt;
	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainRoom() == false) {
		CHECK_ERROR(ERROR_CODE::ROOM_LEAVE_INVALID_DOMAIN);
	}

	auto pLobby = m_pRefLobbyMgr->GetLobby(pUser->GetLobbyIndex());
	if (pLobby == nullptr) {
		CHECK_ERROR(ERROR_CODE::ROOM_LEAVE_INVALID_LOBBY_INDEX);
	}

	auto pRoom = pLobby->GetRoom(pUser->GetRoomIndex());
	pUser->LeaveRoom();
	pRoom->LeaveUser(pUser->GetIndex());
	pRoom->NotifyLeaveUserInfo(std::string(pUser->GetID()).c_str());

	//auto ret = m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_LEAVE_RES, sizeof(resPkt), (char*)&resPkt);
	
	Packet::PktLobbyEnterRes resPkt2;
	auto enterRet = pLobby->EnterUser(pUser);
	pUser->EnterLobby(pLobby->GetIndex());
	if (enterRet != ERROR_CODE::NONE)
	{
		CHECK_ERROR(enterRet); // 아마도 꽉차서?
	}
	pLobby->NotifyLobbyEnterUserInfo(pUser);
	resPkt2.MaxUserCount = pLobby->MaxRoomCount();
	resPkt2.MaxRoomCount = pLobby->MaxRoomCount();
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_ENTER_RES, sizeof(resPkt2), (char*)&resPkt2);

	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::ROOM_LEAVE_RES, sizeof(Packet::PktRoomLeaveRes), (char*)&resPkt);
	return (ERROR_CODE)__result;
}

ERROR_CODE PacketProcess::RoomChat(PacketInfo packetInfo)
{
	return ERROR_CODE();
}

ERROR_CODE PacketProcess::LobbyChat(PacketInfo packetInfo)
{
	CHECK_START;

	auto reqPkt = (Packet::PktLobbyChatReq*)packetInfo.pRefData;
	Packet::PktLobbyChatRes resPkt;

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);

	if (pUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::LOBBY_CHAT_INVALID_DOMAIN);
	}

	auto lobbyIndex = pUser->GetLobbyIndex();
	auto pLobby = m_pRefLobbyMgr->GetLobby(lobbyIndex);
	if (pLobby == nullptr) {
		CHECK_ERROR(ERROR_CODE::LOBBY_CHAT_INVALID_LOBBY_INDEX);
	}

	//같은 로비에 있는 사람에게 메세지 전송
	pLobby->NotifyChat(pUser->GetSessionIndex(), pUser->GetID().c_str(), reqPkt->Msg);

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_CHAT_RES, sizeof(resPkt), (char*)&resPkt);
	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_CHAT_RES, sizeof(resPkt), (char*)&resPkt);
	return (ERROR_CODE)__result;
}

ERROR_CODE PacketProcess::LobbyWhisper(PacketInfo packetInfo)
{
	CHECK_START;
	auto reqPkt = (Packet::PktLobbyWhisperReq*)packetInfo.pRefData;
	Packet::PktLobbyWhisperRes resPkt;

	auto pUserRet = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	auto errorCode = std::get<0>(pUserRet);

	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pTargetUserRet = m_pRefUserMgr->GetUser(reqPkt->TargetUserID);
	errorCode = std::get<0>(pTargetUserRet);
	if (errorCode != ERROR_CODE::NONE) {
		CHECK_ERROR(errorCode);
	}

	auto pUser = std::get<1>(pUserRet);
	if (pUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::LOBBY_WHISPER_INVALID_DOMAIN);
	}

	auto pTargetUser = std::get<1>(pTargetUserRet);
	if (pTargetUser->IsCurDomainLobby() == false) {
		CHECK_ERROR(ERROR_CODE::LOBBY_WHISPER_INVALID_DOMAIN);
	}

	auto lobbyIndex = pUser->GetLobbyIndex();
	auto targetLobbyIndex = pTargetUser->GetLobbyIndex();
	auto pLobby = m_pRefLobbyMgr->GetLobby(lobbyIndex);
	auto targetLobby = m_pRefLobbyMgr->GetLobby(targetLobbyIndex);

	if (pLobby == nullptr || targetLobby == nullptr || lobbyIndex != targetLobbyIndex) {
		CHECK_ERROR(ERROR_CODE::LOBBY_WHISPER_INVALID_LOBBY_INDEX);
	}

	//타겟 유저에게 메세지 전송
	pLobby->NotifyWhisper(pTargetUser->GetSessionIndex(), pUser->GetID().c_str(), pTargetUser->GetID().c_str() , reqPkt->Msg);

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_WHISPER_RES, sizeof(resPkt), (char*)&resPkt);
	return ERROR_CODE::NONE;

CHECK_ERR:
	resPkt.SetError(__result);
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::LOBBY_WHISPER_RES, sizeof(resPkt), (char*)&resPkt);
	return (ERROR_CODE)__result;
}
