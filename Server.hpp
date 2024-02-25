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
#include "chrono"
#include "Config.hpp"

class Server
{

private:
    int server_fd;
    sockaddr_in serverAddress; 
    std::vector<std::thread> clients;
    std::queue<Message> commands;
    Timer timer;
    std::mutex commandMutex;
    std::mutex timerMutex;
    int displayColor;
    bool isServerActive;

    void setup();
    void handleClient(int &client_fd);
    void executeCommands();
    void acceptClients();
    void commandHandler(std::string &&command);
    void timeDisplayer();

public:

    Server();
    void run();
    ~Server();
};

#endif