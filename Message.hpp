#ifndef MESSAGE
#define MESSAGE
#include <iostream>

class Message
{
private:
    // std::string info; maybe server will send sth to client
    std::string command;
    int color; // This will change color of server's timer display - it is for this class to have more sense

    int colorAnalyzer(char *color);
    void deserialize(char *serialized_msg);

public:
    Message(char *serialized_msg);
    Message(char *command, char *color);
    Message(Message &msg);
    std::string getCommand();
    int getColor();
    char *serialize(); // cant be bigger than 1024 chars
};

#endif