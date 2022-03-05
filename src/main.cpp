#include "Radio.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <asio.hpp>

void usage() {
    std::cerr << "Usage: BC95XLT_prog R|W serialport\n"
    "Examples:\n"
    "BC95XLT_prog R /dev/ttyUSB1 > channel.txt\n"
    "BC95XLT_prog W /dev/ttyUSB1 < channel.txt\n";
}

void read(const char* portname) {
    try {
        asio::io_context io_context;
        Radio scanner(io_context, portname);
        std::cout << "# " << scanner.getModel() 
            << "\n# " << scanner.getVersion() << '\n';
        scanner.programMode(true);
        for (int i=1; i < 201; ++i) {
            auto str = scanner.readChannel(i);
            Channel ch(str);
            std::cout << ch << '\n';
        }
        scanner.programMode(false);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

void write(const char* portname) {
    try {
        asio::io_context io_context;
        Radio scanner(io_context, portname);
        std::cout << "# " << scanner.getModel() 
            << "\n# " << scanner.getVersion() << '\n';
        scanner.programMode(true);
        for (std::string line; std::getline(std::cin, line); ) {
            // is it a comment?
            if (line.front() != '#') {
                Channel ch(line, true);
                scanner.writeChannel(ch);
                std::cout << ch << '\n';
            } else {
                std::cout << line << '\n';
            }
        }
        scanner.programMode(false);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char *argv[])
{
    using namespace std::literals;
    if (argc == 3) {
        std::string_view command{argv[1]};
        if (command == "R"sv) {
            read(argv[2]);
        } else if (command == "W"sv) {
            write(argv[2]);
        } else {
            usage();
        }
    } else {
        usage();
    }
}
