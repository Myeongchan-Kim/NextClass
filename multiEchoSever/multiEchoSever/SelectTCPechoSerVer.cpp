#include "SelectTCPechoSerVer.h"



SelectTCPechoSerVer::SelectTCPechoSerVer()
{
}


SelectTCPechoSerVer::~SelectTCPechoSerVer()
{
}

int SelectTCPechoSerVer::run()
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket() err");


	return 0;
}

BOOL SelectTCPechoSerVer::AddSocketInfo(SOCKET sock)
{
	return 0;
}

void SelectTCPechoSerVer::RemoveSocketInfo(int nIndex)
{
}
