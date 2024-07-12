// standard operations c++
#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
// network libs
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <wait.h>

#include "CClientConn.h"

#define IPv4 AF_INET
#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM

constexpr int MAX_CLIENTS = 5;

class CServer {
  public:
    CServer ( int port );
    ~CServer ();
    void server_bind   ();
    void server_listen ();
    void server_run    ();
    
  private:
    struct sockaddr_in m_ServerAddress;
    int                m_ServerSocket;
    int                m_ClientSocket;
    int                m_BytesRead;
};

