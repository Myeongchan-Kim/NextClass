#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 23452
#define BUFSIZE    512

//���� ��� �Լ�
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len; // ���� ���ڿ� ����?

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}


int main(int argc, char *argv[])
{
	int ret;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket() err");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	//serveraddr.sin_port = htons(SERVERPORT);

	ret = inet_pton(AF_INET, SERVERIP, (void*)&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	if (ret != 1)
	{
		err_quit("inet_pton() err");
	}

	ret = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (ret == SOCKET_ERROR)
	{
		err_quit("connect() err");
	}

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len;

	/******������ ������ ���*******/ 
	while (1) {
		// ������ �Է�
		printf("\n[���� ������] : ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' ���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// ������ ������
		ret = send(sock, buf, strlen(buf), 0);
		printf("[TCP client] %dbyte is sended.\n", ret);

		// ������ �ޱ�
		ret = recvn(sock, buf, ret, 0);
		if (ret == SOCKET_ERROR)
		{
			err_display("recv() err");
		}
		else if (ret == 0)
			break;

		// ���� ������ ���
		buf[ret] = '\0';
		printf("[TCP client] %dbyte is recived.\n ", ret);
		printf("[received data] %s\n", buf);
	}

	// closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}