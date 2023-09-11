#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "EChoice.h"
#include <thread>
#include <vector>
#include <mutex>
#include "Timer.h"

class Server
{
private:
    int server_fd;
    sockaddr_in server_address;
    std::vector<std::thread> client_threads;

    void handle_client(int &&client_fd);

public:
    Server();

    ~Server();

    void run();
};

#endif