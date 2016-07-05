#include "User.h"

User::User()
{
}


User::~User()
{
}

void User::Clear()
{
	m_IsConfirm = false;
	m_CurDomainState = DOMAIN_STATE::NONE;
	m_ID = "";

	m_Index = -1;
	m_SessionIndex = -1;
	m_RoomIndex = -1;
	m_LobbyIndex = -1;
}

void User::Set(const int sessionId, const char * userName)
{
	m_IsConfirm = true;
	m_CurDomainState = DOMAIN_STATE::LOGIN;

	m_SessionIndex = sessionId;
	m_ID = userName;
}
