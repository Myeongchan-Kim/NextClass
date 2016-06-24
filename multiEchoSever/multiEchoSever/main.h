#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

#define SERVERPORT 23452
#define BUFSIZE    512

using namespace std;

void err_quit(char *msg);
void err_display(char *msg);
