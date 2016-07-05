#pragma once

#include <vector>
#include <string>
#include "Common.h"

class User;
class ITcpNetwork; 
class ILog; 
using ERROR_CODE = Common::ERROR_CODE;
using TcpNet = ITcpNetwork;

class Room
{
public:
	Room() {};
	virtual ~Room() {};

	void Init(const short index, const short maxUserCount);

	void SetNetwork(TcpNet* pNetwork, ILog* pLogger);

	void Clear();

	short GetIndex() { return m_Index; }

	bool IsUsed() { return m_IsUsed; }

	const wchar_t* GetTitle() { return m_Title.c_str(); }

	short MaxUserCount() { return m_MaxUserCount; }

	short GetUserCount() { return (short)m_UserList.size(); }

	ERROR_CODE CreateRoom(const wchar_t* pRoomTitle);

	ERROR_CODE EnterUser(User* pUser);

	ERROR_CODE LeaveUser(const short userIndex);


	void SendToAllUser(const short packetId, const short dataSize, char* pData, const int passUserindex = -1);

	void NotifyEnterUserInfo(const int userIndex, const char* pszUserID);

	void NotifyLeaveUserInfo(const char* pszUserID);

	void NotifyChat(const int sessionIndex, const char* pszUserID, const wchar_t* pszMsg);

private:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;

	short m_Index = -1;
	short m_MaxUserCount;

	bool m_IsUsed = false;
	std::wstring m_Title;
	std::vector<User*> m_UserList;
};