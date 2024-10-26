#ifndef SERVER_HPP
#define SERVER_HPP

#include "store.hpp" // Include the Store class for key-value storage
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib") // Link Winsock library for Windows
using socket_t = SOCKET;
#define CLOSE_SOCKET closesocket
#define SOCKET_ERROR_CODE WSAGetLastError()
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using socket_t = int;
#define CLOSE_SOCKET close
#define SOCKET_ERROR_CODE errno
#endif

class Server {
  public:
    Server(int port, Store &store);
    void start();

  private:
    int port_;
    Store &store_;

    void handleClient(socket_t client_socket);
    std::string processCommand(const std::string &command);
    void cleanup();
};

#endif // SERVER_HPP
