#include "SocketUtil.h"

#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <iostream>

using std::cerr;
using std::endl;

bool LookupName(char* name,
                unsigned short port,
                struct sockaddr_storage* ret_addr,
                size_t* ret_addrlen) {
  // TODO: fill in this function
  struct addrinfo hints, *results;
  int retval;

  // set all the bytes of hints to be 0
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup by invoking getaddrinfo().
  if ((retval = getaddrinfo(name, nullptr, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }

  // Set the port in the first result.
  if (results->ai_family == AF_INET) {
    struct sockaddr_in* v4addr =
            reinterpret_cast<struct sockaddr_in*>(results->ai_addr);
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    struct sockaddr_in6* v6addr =
            reinterpret_cast<struct sockaddr_in6*>(results->ai_addr);
    v6addr->sin6_port = htons(port);
  } else {
    std::cerr << "getaddrinfo failed to provide an IPv4 or IPv6 address";
    std::cerr << std::endl;
    freeaddrinfo(results);
    return false;
  }

  // Return the first result.
  assert(results != nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;

  // Clean up.
  freeaddrinfo(results);
  return true;

}

bool Connect(const struct sockaddr_storage& addr,
             const size_t& addrlen,
             int* ret_fd) {
  // TODO: fill in this function
  // Create the socket.
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }

  // Connect the socket to the remote host.
  int res = connect(socket_fd,
                    reinterpret_cast<const sockaddr*>(&addr),
                    addrlen);
  if (res == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    return false;
  }

  *ret_fd = socket_fd;
  return true;
}

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  // TODO: fill in this function
  int total_bytes = 0;
  int remaining = readlen;

  while (remaining > 0) {
    int bytes_read = read(fd, buf + total_bytes, remaining);

    if (bytes_read == -1) {
      if (errno == EINTR || errno == EAGAIN) {
        continue;
      } else {
        std::cerr << "Error from reading the file" << strerror(errno) << std::endl;
        close(fd);
        return -1;
      }
    } else if (bytes_read == 0) {
      break;
    }

    total_bytes += bytes_read;
    remaining -= bytes_read;
  }

  close(fd);
  return total_bytes;
}

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
  // TODO: fill in this function
  int total_written = 0;
  int remaining = writelen;

  while (remaining > 0) {
    int bytes_written = write(fd, buf + total_written, remaining);

    if (bytes_written == -1) {
      if (errno == EINTR || errno == EAGAIN) {
        continue;
      } else {
        std::cerr << "Error from writing the file" << strerror(errno) << std::endl;
        close(fd);
        return -1;
      }
    } else if (bytes_written == 0) {
      break;
    }
    
    total_written += bytes_written;
    remaining -= bytes_written;
  }
  
  close(fd);
  return total_written;
}
