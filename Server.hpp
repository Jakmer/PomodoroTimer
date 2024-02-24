#ifndef SERVER        
#define SERVER

#include <iostream>
#include <vector>
#include <netinet/in.h>
#include "Client.hpp"
#include "Message.hpp"
#include "Timer.hpp"
#include <queue>
#include <thread>
#include <sys/socket.h>
#include <mutex>

class Server
{

private:
    int server_fd;
    sockaddr_in serverAddress; 
    std::vector<std::thread> clients;
    std::queue<Message> commands;
    Timer timer;
    std::mutex mutex;
    bool isServerActive;

    void setup();
    void handleClient(int &client_fd);
    void executeCommands();
    void acceptClients();

public:

    Server();
    void run();
    ~Server();
};

#endif