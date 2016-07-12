#include <algorithm>

#include "ILog.h"
#include "TcpNetwork.h"
#include "Packet.h"
#include "ServerConfig.h"

#include "User.h"
#include "Room.h"

using PACKET_ID = Common::PACKET_ID;

void Room::Init(const short index, const short maxUserCount)
{
	m_Index = index;
	m_MaxUserCount = maxUserCount;
}

void Room::SetNetwork(TcpNet* pNetwork, ILog* pLogger)
{
	m_pRefLogger = pLogger;
	m_pRefNetwork = pNetwork;
}

void Room::Clear()
{
	m_IsUsed = false;
	m_Title = L"";
	m_UserList.clear();
}

ERROR_CODE Room::CreateRoom(const wchar_t* pRoomTitle)
{
	if (m_IsUsed) {
		return ERROR_CODE::ROOM_ENTER_CREATE_FAIL;
	}

	m_IsUsed = true;
	m_Title = pRoomTitle;

	return ERROR_CODE::NONE;
}

ERROR_CODE Room::EnterUser(User* pUser)
{
	if (m_IsUsed == false) {
		return ERROR_CODE::ROOM_ENTER_NOT_CREATED;
	}

	if (m_UserList.size() == m_MaxUserCount) {
		return ERROR_CODE::ROOM_ENTER_MEMBER_FULL;
	}

	m_UserList.push_back(pUser);
	return ERROR_CODE::NONE;
}

ERROR_CODE Room::LeaveUser(const short userIndex)
{
	if (m_IsUsed == false) {
		return ERROR_CODE::ROOM_ENTER_NOT_CREATED;
	}

	auto iter = std::find_if(std::begin(m_UserList), std::end(m_UserList), [userIndex](auto pUser) { return pUser->GetIndex() == userIndex; });
	if (iter == std::end(m_UserList)) {
		return ERROR_CODE::ROOM_LEAVE_NOT_MEMBER;
	}

	m_UserList.erase(iter);

	if (m_UserList.empty())
	{
		Clear();
	}

	return ERROR_CODE::NONE;
}

void Room::SendToAllUser(const short packetId, const short dataSize, char* pData, const int passUserindex)
{
	for (auto pUser : m_UserList)
	{
		if (pUser->GetIndex() == passUserindex) {
			continue;
		}

		m_pRefNetwork->SendData(pUser->GetSessionIndex(), packetId, dataSize, pData);
	}
}

void Room::NotifyEnterUserInfo(const int userIndex, const char* pszUserID)
{
	Packet::PktRoomEnterUserInfoNtf pkt;
	strncpy_s(pkt.UserID, _countof(pkt.UserID), pszUserID, Packet::MAX_USER_ID_SIZE);

	SendToAllUser((short)PACKET_ID::ROOM_ENTER_USER_NTF, sizeof(pkt), (char*)&pkt, userIndex);
}

void Room::NotifyLeaveUserInfo(const char* pszUserID)
{
	if (m_IsUsed == false) {
		return;
	}

	Packet::PktRoomLeaveUserInfoNtf pkt;
	strncpy_s(pkt.UserID, _countof(pkt.UserID), pszUserID, Packet::MAX_USER_ID_SIZE);

	SendToAllUser((short)PACKET_ID::ROOM_LEAVE_USER_NTF, sizeof(pkt), (char*)&pkt);
}

void Room::NotifyChat(const int sessionIndex, const char* pszUserID, const wchar_t* pszMsg)
{
	Packet::PktRoomChatNtf pkt;
	strncpy_s(pkt.UserID, _countof(pkt.UserID), pszUserID, Packet::MAX_USER_ID_SIZE);
	wcsncpy_s(pkt.Msg, Packet::MAX_ROOM_CHAT_MSG_SIZE + 1, pszMsg, Packet::MAX_ROOM_CHAT_MSG_SIZE);

	SendToAllUser((short)PACKET_ID::ROOM_CHAT_NTF, sizeof(pkt), (char*)&pkt, sessionIndex);
}

std::string Room::GetUserID(const int i)
{
	return m_UserList[i]->GetID();
}
