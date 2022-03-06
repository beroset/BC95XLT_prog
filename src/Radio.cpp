#include "Radio.h"

#include <sstream>
#include <string_view>
#include <asio.hpp>


class Radio {
public:
    Radio(asio::io_context& io_context, const char* portname, bool verbose);
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
    bool verbosity = false;
    asio::serial_port port;
    asio::io_context& io_context;
};

Radio::Radio(asio::io_context& io_context, const char* portname, bool verbose)
    : io_context{io_context}
    , port(io_context, portname)
    , verbosity{verbose}
{
    port.set_option(asio::serial_port_base::baud_rate(9600));
}

std::string Radio::doCommand(std::string_view cmd) {
    if (verbosity) std::cerr << "TX:" << cmd << '\n';
    asio::write(port, asio::buffer(cmd));
    std::string buffer;
    auto bytes = asio::read_until(port, asio::dynamic_buffer(buffer), '\r');
    if (verbosity) std::cerr << "RX:" << buffer << '\n';
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

RadioContents read_radio(const char* portname, bool verbose) {
    RadioContents radio_data;
    try {
        asio::io_context io_context;
        Radio scanner(io_context, portname, verbose);
        radio_data.model = scanner.getModel();
        radio_data.version = scanner.getVersion();
        scanner.programMode(true);
        for (int i=1; i <= 200; ++i) {
            auto str = scanner.readChannel(i);
            radio_data.channel_list.emplace_back(Channel{str});
        }
        scanner.programMode(false);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return radio_data;
}

void write_radio(const char* portname, const RadioContents& radio_data, bool verbose) {
    try {
        asio::io_context io_context;
        Radio scanner(io_context, portname, verbose);
        scanner.programMode(true);
        for (const auto& channel : radio_data.channel_list) {
            scanner.writeChannel(channel);
        }
        scanner.programMode(false);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

std::ostream& operator<<(std::ostream& out, const RadioContents& radio_contents) {
    out << "# model: " << radio_contents.model
        << "\n# version: " << radio_contents.version << '\n';
    for (const auto& channel : radio_contents.channel_list) {
        out << channel << '\n';
    }
    return out;
}

std::istream& operator>>(std::istream& in, RadioContents& radio_contents) {
    for (std::string line; std::getline(in, line); ) {
        if (line.front() == '#') 
            continue;
        radio_contents.channel_list.emplace_back(Channel{line, true});
    }
    return in;
}
