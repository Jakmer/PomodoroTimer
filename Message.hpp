#ifndef MESSAGE
#define MESSAGE
#include <iostream>
#include "Config.hpp"

class Message
{
private:
    std::string command;
    int color; 

    int colorAnalyzer(std::string &color);
    void deserialize(char *serialized_msg);

public:
    Message(char *serialized_msg);
    Message(char *command, char *color);
    Message(Message &msg);
    Message();
    std::string getCommand();
    int getColor();
    char *serialize(); 
};

#endif