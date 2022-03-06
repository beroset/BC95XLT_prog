#include "Radio.h"

#include <iostream>
#include <stdexcept>
#include <string>

void usage() {
    std::cerr << "Usage: BC95XLT_prog R|W serialport\n"
    "Examples:\n"
    "BC95XLT_prog R /dev/ttyUSB1 > channel.txt\n"
    "BC95XLT_prog W /dev/ttyUSB1 < channel.txt\n";
}

int main(int argc, char *argv[])
{
    using namespace std::literals;
    if (argc == 3) {
        std::string_view command{argv[1]};
        if (command == "R"sv) {
            RadioContents contents = read_radio(argv[2]);
            std::cout << contents;
        } else if (command == "W"sv) {
            RadioContents contents;
            std::cin >> contents;
            write_radio(argv[2], contents);
        } else {
            usage();
        }
    } else {
        usage();
    }
}
