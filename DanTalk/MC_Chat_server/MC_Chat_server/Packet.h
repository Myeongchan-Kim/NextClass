#pragma once
#include "Common.h"
using ERROR_CODE = Common::ERROR_CODE;

class Packet
{
#pragma pack(push, 1)
public:
	static const int MAX_USER_ID_SIZE = 16;
	static const int MAX_USER_PASSWORD_SIZE = 16;
	static const int MAX_LOBBY_LIST_COUNT = 20;
	static const int MAX_ROOM_TITLE_SIZE = 16;
	static const int MAX_NTF_LOBBY_ROOM_LIST_COUNT = 12;
	static const int MAX_SEND_LOBBY_USER_LIST_COUNT = 32;
	static const int MAX_ROOM_CHAT_MSG_SIZE = 256;
	static const int MAX_LOBBY_CHAT_MSG_SIZE = 256;

	struct PktHeader
	{
		short Id;
		short BodySize;
	};

	struct PktBase
	{
		short ErrorCode = (short)ERROR_CODE::NONE;
		void SetError(ERROR_CODE error) { ErrorCode = (short)error; }
	};

	//- �α��� ��û
	struct PktLogInReq
	{
		char szID[MAX_USER_ID_SIZE + 1] = { 0, };
		char szPW[MAX_USER_PASSWORD_SIZE + 1] = { 0, };
	};

	struct PktLogInRes : PktBase
	{
	};


	//- ä�� ����Ʈ ��û
	struct LobbyListInfo
	{
		short LobbyId;
		short LobbyUserCount;
	};
	struct PktLobbyListRes : PktBase
	{
		short LobbyCount = 0;
		LobbyListInfo LobbyList[MAX_LOBBY_LIST_COUNT];
	};


	//- �κ� ���� ��û
	struct PktLobbyEnterReq
	{
		short LobbyId;
	};

	struct PktLobbyEnterRes : PktBase
	{
		short MaxUserCount;
		short MaxRoomCount;
	};


	//- �κ� �ִ� �������� �κ� ���� ���� �뺸
	struct PktLobbyNewUserInfoNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
	};


	//- �κ��� �� ����Ʈ ��û
	struct PktLobbyRoomListReq
	{
		short StartRoomIndex; // �κ񿡼� ó�� ��û�� ���� 0, �ι�°���ʹ� �տ� ���� �������� ������ ��ȣ + 1
	};

	struct RoomSmallInfo
	{
		short RoomIndex;
		short RoomUserCount;
		wchar_t RoomTitle[MAX_ROOM_TITLE_SIZE + 1] = { 0, };
	};

	struct PktLobbyRoomListRes : PktBase
	{
		bool IsEnd = false; // true �̸� �� �̻� �� ����Ʈ ��û�� ���� �ʴ´�
		short Count = 0;
		RoomSmallInfo RoomInfo[MAX_NTF_LOBBY_ROOM_LIST_COUNT];
	};


	//- �κ��� ���� ����Ʈ ��û
	struct PktLobbyUserListReq
	{
		short StartUserIndex;
	};

	struct UserSmallInfo
	{
		short LobbyUserIndex;
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
	};

	struct PktLobbyUserListRes : PktBase
	{
		bool IsEnd = false; // true �̸� �� �̻� �� ����Ʈ ��û�� ���� �ʴ´�
		short Count = 0;
		UserSmallInfo UserInfo[MAX_SEND_LOBBY_USER_LIST_COUNT];
	};


	//- �κ񿡼� ������ ��û
	struct PktLobbyLeaveReq {};

	struct PktLobbyLeaveRes : PktBase
	{
	};

	//- �κ񿡼� ������ ���� �뺸(�κ� �ִ� ��������)
	struct PktLobbyLeaveUserInfoNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
	};


	//- �뿡 ���� ��û
	struct PktRoomEnterReq
	{
		bool IsCreate;
		short RoomIndex;
		wchar_t RoomTitle[MAX_ROOM_TITLE_SIZE + 1];
	};

	struct PktRoomEnterRes : PktBase
	{
	};


	//- ����� �� ���� �뺸
	struct PktChangedRoomInfoNtf
	{
		RoomSmallInfo RoomInfo;
	};

	//- �뿡 �ִ� �������� ���� ���� ���� ���� �뺸
	struct PktRoomEnterUserInfoNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
	};


	//- �� ������ ��û
	struct PktRoomLeaveReq {};

	struct PktRoomLeaveRes : PktBase
	{
	};

	//- �뿡�� ������ ���� �뺸(�κ� �ִ� ��������)
	struct PktRoomLeaveUserInfoNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
	};


	//- �� ä��
	struct PktRoomChatReq
	{
		wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE + 1] = { 0, };
	};

	struct PktRoomChatRes : PktBase
	{
	};

	struct PktRoomChatNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
		wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE + 1] = { 0, };
	};

	//- �κ� ä��
	struct PktLobbyChatReq
	{
		wchar_t Msg[MAX_LOBBY_CHAT_MSG_SIZE + 1] = { 0, };
	};

	struct PktLobbyChatRes : PktBase
	{
	};

	struct PktLobbyChatNtf
	{
		char UserID[MAX_USER_ID_SIZE + 1] = { 0, };
		wchar_t Msg[MAX_LOBBY_CHAT_MSG_SIZE + 1] = { 0, };
	};


	//
	struct RecvPacketInfo
	{
		int SessionIndex = 0;
		short PacketId = 0;
		short PacketBodySize = 0;
		char* pRefData = 0;
	};

	struct RecvPacketInfo2
	{
		int SessionIndex = 0;
		short PacketId = 0;
		short PacketBodySize = 0;
		char* pRefData = 0;
	};

#pragma pack(pop)
};

