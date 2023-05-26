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
#include <fcntl.h>
#include <iostream>
#include "SocketUtil.h"

#define BUFFSIZE 1024

void Usage(char* progname);
void HandleClient(int c_fd, struct sockaddr* addr, size_t addrlen,
                  int sock_family);

// Create a listening socket, accept a connection from a client,
// and write all the data the client sends to stdout.
int main(int argc, char** argv) {
  // TODO: fill in this main method
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);
  int client_fd = accept(listen_fd,
                          reinterpret_cast<struct sockaddr*>(&caddr),
                          &caddr_len);
  if (client_fd < 0) {
    std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  HandleClient(client_fd,
                reinterpret_cast<struct sockaddr*>(&caddr),
                caddr_len,
                sock_family);


  return 0;

}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}

void HandleClient(int c_fd, struct sockaddr* addr, size_t addrlen,
                  int sock_family) {

  while (1) {
    unsigned char clientbuf[1024];
    ssize_t res = WrappedRead(c_fd, clientbuf, BUFFSIZE);
    if (res == 0) {
      std::cout << " [The client disconnected.]" << std::endl;
      break;
    }

    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;

      std::cout << " [Error on client socket: ";
      std::cout << strerror(errno) << "]" << std::endl;
      break;
    }
    if (WrappedWrite(STDOUT_FILENO, clientbuf, res) == -1) {  // < buffsize
      close(STDOUT_FILENO);
      close(c_fd);
      break;
    }
  }
  close(c_fd);
}