//============================CLIENT==================================

// standard operations c++
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
// network libs
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <wait.h>
// client libs
#include <netdb.h>

#define IPv4 AF_INET
#define TCP SOCK_STREAM

const int BUFFER_SIZE = 10240;

int main(int argc, char **argv){

  if ( argc < 3 ){
    cerr << "Client: need address port" << endl;
    return EXIT_FAILURE;
  }
  cout << "Hello Client!" << endl;

  int s = socket(IPv4, TCP, 0);
  if ( s < 0){
    perror( "Client: cannot create socket" );
    return EXIT_FAILURE;
  }

  int port = atoi(argv[2]);
  if ( port == 0){
    cerr << "Client: cannot read port or port is 0." << endl;
    close (s);
    return EXIT_FAILURE;
  }

  struct sockaddr_in serverAddr = {};

  serverAddr.sin_family = IPv4;
  serverAddr.sin_port = htons(port);

  struct hostent * host;
  host = gethostbyname(argv[1]);
  memcpy(&serverAddr.sin_addr, host->h_addr, host->h_length);

  if (connect (s, (struct sockaddr *) &serverAddr, sizeof(serverAddr) ) < 0){
    perror("Client: connection failed");
    close(s);
    return EXIT_FAILURE;
  }

  char buffer [BUFFER_SIZE];
/* 
    int bytesRead = recv(s, buffer, BUFFER_SIZE - 1, 0);
    if (bytesRead <= 0){
      perror("Server: error reading from client");
      close (s);
      return false;
    }
    cout << buffer << endl; */

  while (true){
    cout << "> ";
    cin.getline(buffer, BUFFER_SIZE - 1);
    if (send(s, buffer, strlen(buffer),MSG_NOSIGNAL) < 0){
      perror ("Client: couldn't send buffer");
      close(s);
      return EXIT_FAILURE;
    }
    if (string("exit") == buffer){
      break;
    }
  }
  

  close(s);
  return EXIT_SUCCESS;
}