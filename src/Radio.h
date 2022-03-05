#ifndef MY_RADIO_H
#define MY_RADIO_H

#include "Channel.h"
#include <string>
#include <string_view>
#include <asio.hpp>

class Radio {
public:
    Radio(asio::io_context& io_context, const char* portname);
    std::string getModel();
    std::string getVersion();
    std::string readChannel(uint8_t channel);
    std::string writeChannel(const Channel& channel);
    bool programMode(bool mode);
private:
    std::string enterProgMode();
    std::string leaveProgMode();
    std::string doCommand(std::string_view cmd);
    bool progmode = false;
    asio::serial_port port;
    asio::io_context& io_context;
};
#endif // MY_RADIO_H
