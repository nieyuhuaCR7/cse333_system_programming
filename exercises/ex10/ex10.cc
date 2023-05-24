#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "SocketUtil.h"

#include <iostream>

void Usage(char* progname);

// Open a local file, open a socket to a remote process,
// and send the file to other process.
int main(int argc, char** argv) {
  // Expect the port number as a command line argument.
  if (argc != 4) {
    Usage(argv[0]);
  }

  char* hostname = argv[1];
  unsigned short port = std::stoi(argv[2]);
  std::string filename = argv[3];

  struct sockaddr_storage serverAddr;
  size_t addrlen;

  // Get an appropriate sockaddr structure.
  if (!LookupName(hostname, port, &serverAddr, &addrlen)) {
    Usage(argv[0]);
  }

  // connect to the remote server
  int socket_fd;
  if (!Connect(serverAddr, addrlen, &socket_fd)) {
    Usage(argv[0]);
  }

  

}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " <hostname> <port> <filename>" << std::endl;
  exit(EXIT_FAILURE);
}