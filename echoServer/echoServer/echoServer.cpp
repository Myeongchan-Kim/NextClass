#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 23452
#define BUFSIZE    512

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

int main(int argc, char *argv[])
{
	int ret;

	//winsock 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("sockt() err");

	//bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	ret = inet_pton(AF_INET, INADDR_ANY, (void*)&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	ret = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR) err_quit("bind() err");

	// listen()
	ret = listen(listen_sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) err_quit("listen() err");

	//vaiable for data in and out;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1)
	{
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)& clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept() err");
			break;
		}

		// 접속한 클라이언트 정보 출력
		char clientIP[32] = { 0, };
		inet_ntop(AF_INET, &(clientaddr.sin_addr), clientIP, 32 - 1);
		printf("\n[TCP server] client connected : IP=%s, port=%d\n", clientIP, ntohs(clientaddr.sin_port));

		// 클라이언트와 데이터 통신
		while (1) 
		{
			//data receive
			ret = recv(client_sock, buf, BUFSIZE, 0);
			if (ret == SOCKET_ERROR)
			{
				err_display("recv() err");
				break;
			}
			else if (ret == 0)
				break;

			//print received data
			buf[ret] = '\0';
			printf("[TCP/%s:%d] %s\n", clientIP, ntohs(clientaddr.sin_port), buf);

			//데이터 보내기
			ret = send(client_sock, buf, ret, 0);
			if (ret == SOCKET_ERROR)
			{
				err_display("send() err");
				break;
			}
		}
		// closesocket()
		closesocket(client_sock);
		printf("[TCP server] client quit: IP=%s, port=%d\n", clientIP, ntohs(clientaddr.sin_port));
	}

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}