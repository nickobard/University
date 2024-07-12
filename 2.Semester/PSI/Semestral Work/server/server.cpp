//============================SERVER==================================

#include "CServer.h"

int main(int argc, char **argv){

  if ( argc < 2 ){
    cerr << "Server: need address port" << endl;
    return EXIT_FAILURE;
  }

  cout << "Hello Server!" << endl;

  CServer server (atoi(argv[1]));

  server.server_bind();
  server.server_listen(); 
  server.server_run();

  return EXIT_SUCCESS;
}