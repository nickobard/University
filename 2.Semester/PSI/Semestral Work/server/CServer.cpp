#include "CServer.h"

CServer::CServer (int port) {
  m_ServerSocket = socket(IPv4, TCP, 0);
  if ( m_ServerSocket < 0){
    perror( "Server: cannot create socket" );
    throw exception();
  }
  if ( port == 0){
    cerr << "Server: cannot read port or port is 0." << endl;
    close (m_ServerSocket);
    throw exception();
  }
  bzero (&m_ServerAddress, sizeof(m_ServerAddress));
  m_ServerAddress.sin_family = IPv4;
  m_ServerAddress.sin_port = htons(port);
  m_ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}

CServer::~CServer (){
  close(m_ServerSocket);
}

void CServer::server_bind () {
  if (bind(m_ServerSocket,
          (struct sockaddr *) &m_ServerAddress,
           sizeof(m_ServerAddress)) < 0){
    IN_FUNC;
    perror("Server: bind error");
    throw exception();
  }
}

void CServer::server_listen () {
  if (listen (m_ServerSocket, MAX_CLIENTS) < 0 ){
    IN_FUNC;
    perror("Server: listen error");
    throw exception();
  }
}

void CServer::server_run () {

  struct sockaddr_in clientAddr;
  socklen_t clientAddrSize;

  while(true){
    m_ClientSocket = accept( m_ServerSocket,
                   (sockaddr *) &clientAddr,
                                &clientAddrSize);
    if (m_ClientSocket < 0){
      IN_FUNC;
      perror("Server: cannot establish connection with client (accept())");
      throw exception();
    }

    pid_t pid = fork();
    if ( pid == 0){
      close (m_ServerSocket);
      CClientConn clientConn (m_ClientSocket);
      clientConn.client_process();
      return;
    }

    int status = 0;
    waitpid(0,&status,WNOHANG);
    close (m_ClientSocket);
  }
}

