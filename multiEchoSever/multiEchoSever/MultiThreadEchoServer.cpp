#include "main.h"
#include "MultiThreadEchoServer.h"


MultiThreadEchoServer::MultiThreadEchoServer(int port): m_serverPort(port)
{
}


MultiThreadEchoServer::~MultiThreadEchoServer()
{
}

// 클라이언트와 데이터 통신
DWORD WINAPI MultiThreadEchoServer::ProcessClient(LPVOID arg) // arg is client_socket
{
	SOCKET client_socket = (SOCKET)arg;
	int ret;
	SOCKADDR_IN clientAddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	addrlen = sizeof(clientAddr);
	getpeername(client_socket, (SOCKADDR*)&clientAddr, &addrlen);

	//IP 문자열
	char clientIP[32] = { 0, };
	inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, 32 - 1);

	while (1)
	{
		ret = recv(client_socket, buf, BUFSIZE, 0);
		if (ret == SOCKET_ERROR)
		{
			err_display("recv() err");
			break;
		}
		else if (ret == 0)
			break; // reciev complete

		buf[ret] = '\0';
		printf(" [TCP/%s:%d] %s\n", clientIP, ntohs(clientAddr.sin_port), buf);

		ret = send(client_socket, buf, ret, 0);
		if (ret == SOCKET_ERROR)
		{
			err_display("Send() err");
			break;
		}
	}

	// closesocket()
	closesocket(client_socket);
	printf("[TCP server] client disconnected : IP=%s, port=%d\n", clientIP, ntohs(clientAddr.sin_port));

	return 0;
}


int MultiThreadEchoServer::run()
{
	int ret;

	//기본 자원은 단일 에코서버와 동일.
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket() err");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr)); 
	serveraddr.sin_family = AF_INET;

	ret = inet_pton(AF_INET, INADDR_ANY, (void*)&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(m_serverPort);
	ret = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR) err_quit("bind() err");

	ret = listen(listen_sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) err_quit("listen() err");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread; //multithread를 이용함.

	while (1)
	{
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == SOCKET_ERROR)
		{
			err_display("accept() err");
			break;
		}

		//print client information
		char clientIP[32];
		inet_ntop(AF_INET, (void*)&clientaddr.sin_addr, clientIP, 32 - 1);
		printf("[TCP server]client connected: ip=%s port=%d\n", &(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//make thread
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL);

		//release resource
		if (hThread == NULL) // for child
			closesocket(client_sock);
		else
			CloseHandle(hThread); //for parent
	}
	return 0;
}
