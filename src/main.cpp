// redis.cpp : Defines the entry point for the application.
//

#include "server.h"
#include "store.h"

int main() {
    Store store;
    Server server(6379, store); // Default Redis port
    server.start();
    return 0;
}
