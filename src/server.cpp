#include "server.hpp"

Server::Server(int port, Store &store) : port_(port), store_(store) {}

void Server::start() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError()
                  << std::endl;
        return;
    }
#endif

    // Create socket
    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << SOCKET_ERROR_CODE
                  << std::endl;
        cleanup();
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    // Bind and listen
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed with error: " << SOCKET_ERROR_CODE
                  << std::endl;
        CLOSE_SOCKET(server_fd);
        cleanup();
        return;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed with error: " << SOCKET_ERROR_CODE
                  << std::endl;
        CLOSE_SOCKET(server_fd);
        cleanup();
        return;
    }

    std::cout << "Server listening on port " << port_ << std::endl;

    // Accept clients
    while (true) {
        socket_t client_socket = accept(server_fd, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << SOCKET_ERROR_CODE
                      << std::endl;
            continue;
        }
        std::thread(&Server::handleClient, this, client_socket).detach();
    }

    CLOSE_SOCKET(server_fd);
    cleanup();
}

void Server::handleClient(socket_t client_socket) {
    char buffer[1024] = {0};
    while (true) {
        int read_size = recv(client_socket, buffer, 1024, 0);
        if (read_size <= 0)
            break;

        std::string response = processCommand(buffer);
        send(client_socket, response.c_str(), static_cast<int>(response.size()),
             0);
    }
    CLOSE_SOCKET(client_socket);
}

std::string Server::processCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string cmd, key, value;
    iss >> cmd >> key;

    if (cmd == "SET") {
        iss >> value;
        store_.set(key, value);
        return "OK\r\n";
    } else if (cmd == "GET") {
        return store_.get(key) + "\r\n";
    } else if (cmd == "DEL") {
        store_.del(key);
        return "OK\r\n";
    } else if (cmd == "PING") {
        return "PONG\r\n";
    }
    return "ERROR: Unknown command\r\n";
}

void Server::cleanup() {
#ifdef _WIN32
    WSACleanup();
#endif
}
