#pragma once
class MultiThreadEchoServer
{
public:
	MultiThreadEchoServer(int serverPort);
	~MultiThreadEchoServer();

	int run();
protected:
	static DWORD WINAPI ProcessClient(LPVOID arg); // arg is client_socket
	
	int m_serverPort;
};

