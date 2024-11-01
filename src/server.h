#ifndef SERVER_H
#define SERVER_H

#include "commands/command_parser.h"
#include "store.h" // Include the Store class for key-value storage
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
#define INVALID_SOCKET_VALUE INVALID_SOCKET
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using socket_t = int;
#define CLOSE_SOCKET close
#define SOCKET_ERROR_CODE errno
#define INVALID_SOCKET_VALUE -1
#endif

class Server {
  public:
    Server(int port, Store &store);
    void start();

  private:
    int port_;
    Store &store_;

    void handle_client(socket_t client_socket);
    std::string process_command(const std::string &command);
    void cleanup();
};

#endif // SERVER_H
