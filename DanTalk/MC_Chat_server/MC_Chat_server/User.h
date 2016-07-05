#pragma once
#include <string>

class User
{
public:
	enum class DOMAIN_STATE {
		NONE = 0,
		LOGIN = 1, 
		LOBBY = 2,
		ROOM = 3,
	};
	User();
	virtual ~User();

	void Init(const short index) { m_Index = index; }
	void Clear();
	void Set(const int sessionId, const char* userName);

	short GetIndex() { return m_Index; }
	int GetSessionIndex() { return m_SessionIndex; }
	std::string GetID() { return m_ID; }
	bool IsConfirm() { return m_IsConfirm; }
	bool IsCurDomainLogin() { return m_CurDomainState == DOMAIN_STATE::LOGIN; }
	bool IsCurDomainLobby() { return m_CurDomainState == DOMAIN_STATE::LOBBY; }
	bool IsCurDomainRoom() { return m_CurDomainState == DOMAIN_STATE::ROOM; }


	short GetLobbyIndex() { return m_LobbyIndex; }
	void EnterLobby(const short lobbyIndex)
	{
		m_LobbyIndex = lobbyIndex;
		m_CurDomainState = DOMAIN_STATE::LOBBY;
	}
	void LeaveLobby()
	{
		m_LobbyIndex = -1;
		m_CurDomainState = DOMAIN_STATE::LOGIN;
	}

	short GetRoomIndex() { return m_RoomIndex; }
	void EnterRoom(const short lobbyindex, const short roomIndex)
	{
		m_LobbyIndex = lobbyindex;
		m_RoomIndex = roomIndex;
		m_CurDomainState = DOMAIN_STATE::ROOM;
	}

protected:
	short m_Index = -1;
	int m_SessionIndex = -1;
	
	std::string m_ID; //username
	bool m_IsConfirm = false; //로그인 및 세션번호 확인되었는지
	
	DOMAIN_STATE m_CurDomainState = DOMAIN_STATE::NONE;
	short m_LobbyIndex = -1;
	short m_RoomIndex = -1;
};

