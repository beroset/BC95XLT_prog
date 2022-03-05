#include "Radio.h"

#include <sstream>

Radio::Radio(asio::io_context& io_context, const char* portname)
    : io_context{io_context}
    , port(io_context, portname)
{
    port.set_option(asio::serial_port_base::baud_rate(9600));
}

std::string Radio::doCommand(std::string_view cmd) {
    write(port, asio::buffer(cmd));
    std::string buffer;
    auto bytes = asio::read_until(port, asio::dynamic_buffer(buffer), '\r');
    return buffer.substr(0, bytes);
}

std::string Radio::enterProgMode() {
    return doCommand(std::string_view{"PRG\r", 4});
}

std::string Radio::leaveProgMode() {
    return doCommand(std::string_view{"EPG\r", 4});
}

std::string Radio::getModel() {
    return doCommand(std::string_view{"MDL\r", 4});
}

std::string Radio::getVersion() {
    return doCommand(std::string_view{"VER\r", 4});
}

std::string Radio::readChannel(uint8_t channel) {
    if (!progmode) {
        enterProgMode();
    }
    std::stringstream cmd;
    cmd << "RCM^C" << static_cast<int>(channel) << '\r';
    auto answer = doCommand(cmd.str());
    if (!progmode) {
        leaveProgMode();
    }
    return answer;
}

std::string Radio::writeChannel(const Channel& channel) {
    if (!progmode) {
        enterProgMode();
    }
    std::stringstream cmd;
    cmd << "PCM" << channel.toString() << '\r';
    auto answer = doCommand(cmd.str());
    if (!progmode) {
        leaveProgMode();
    }
    return answer;
}

bool Radio::programMode(bool mode) {
    if (mode != progmode) {
        progmode = mode;
        if (mode) {
            enterProgMode();
        } else {
            leaveProgMode();
        }
    }
    return progmode;
}
