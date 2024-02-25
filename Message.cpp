#include "Message.hpp"
#include <string>
#include <string.h>

int Message::colorAnalyzer(std::string &color) 
{
    for(auto it = COLORS.begin(); it!=COLORS.end(); it++)
    {
        if(it->first==color)
        {
            return it->second;
        }
    }

    return COLORS["White"];
}

void Message::deserialize(char *serialized_msg)
{

    try
    {
        std::string msg{serialized_msg};
        
        auto i = msg.find(';');
        command =  msg.substr(0,i);
        color = std::stoi(msg.substr(++i));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Message::Message(){

}

Message::Message(char *serialized_msg)
{
    deserialize(serialized_msg);
}

Message::Message(char *command, char *color) : command(command)
{
    std::string str_color {color};
    this->color = colorAnalyzer(str_color);
}

Message::Message(Message &msg) : command(msg.getCommand()), color(msg.getColor())
{
}

std::string Message::getCommand()
{
    return command;
}

int Message::getColor()
{
    return color;
}

char *Message::serialize()
{
    // cant be bigger than 15 chars - null terminator at the last position
    char *buffer;
    unsigned buffer_size = BUFFER_SIZE;

    try
    {
        if (command.length() + std::to_string(color).length() + 1 < buffer_size)
        {
            buffer = new char[buffer_size];

            strcpy(buffer, command.c_str());

            strcat(buffer, ";");

            strcat(buffer, std::to_string(color).c_str());

            
        }
        else
        {
            throw std::runtime_error("Client: Buffer overload");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return buffer;
}