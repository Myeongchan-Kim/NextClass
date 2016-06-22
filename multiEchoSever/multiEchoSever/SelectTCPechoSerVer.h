#pragma once
#include "main.h"

class SelectTCPechoSerVer
{
public:
	SelectTCPechoSerVer();
	~SelectTCPechoSerVer();

	struct SocketInfo
	{
		SOCKET sock;
		char buf[BUFSIZE + 1];
		int recvbyte;
		int sendbyte;
	};

	int run();
protected:
	int _nTotalSockets = 0;
	SocketInfo* _pSocketInfoArray[FD_SETSIZE];

	BOOL AddSocketInfo(SOCKET sock);
	void RemoveSocketInfo(int nIndex);

};

