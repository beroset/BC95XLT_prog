#include "Channel.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

Boolopt::Boolopt(char ch) {
    on = ch == 'S';
}

std::ostream& operator<<(std::ostream& out, const Boolopt& boolopt) {
    static std::string_view rs{"RS"};
    return out << rs[boolopt.on];
}

std::istream& operator>>(std::istream& in, Boolopt& boolopt) {
    char opt;
    in >> opt;
    if (opt == 'R' || opt == 'S') {
        boolopt = Boolopt{opt};
    } else {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

Channel::Channel(std::string_view line, bool human_readable) {
    std::stringstream buffer(std::string{line});
    bool valid{false};
    if (human_readable) {
        char delim;
        int channelnumber;
        buffer >> channelnumber >> delim;
        buffer >> frequency >> delim;
        buffer >> lockout >> delim;
        buffer >> priority >> delim;
        buffer >> delay;
        number = channelnumber;
        valid = delim == ',';
    } else {
        for(std::string chunk; std::getline(buffer, chunk, '^'); ) {
            char type{chunk.front()};
            chunk.erase(0,1);
            switch(type) {
                case 'C':
                    number = stoi(chunk);
                    break;
                case 'F':
                    frequency = stof(chunk);
                    break;
                case 'L':
                    lockout = Boolopt{chunk.front()};
                    break;
                case 'P':
                    priority = Boolopt{chunk.front()};
                    break;
                case 'D':
                    delay = Boolopt{chunk.front()};
                    valid = true;
                    break;
                default:
                    // probably the first part of the line -- ignore it
                    ;
            }
        }
    }
    if (!valid) {
        throw std::runtime_error("Error reading channel");
    }
}

std::string Channel::toString(bool human_readable) const {
    std::stringstream ss;
    ss << (human_readable ? "" : "^C") << static_cast<int>(number)
                << (human_readable ? "," : "^F") << std::fixed << std::setprecision(4) << frequency
                << (human_readable ? "," : "^L") << lockout
                << (human_readable ? "," : "^P") << priority
                << (human_readable ? "," : "^D") << delay
                ;
    return ss.str();
}

bool Channel::operator<(const Channel& other) {
    return number < other.number;
}

std::ostream& operator<<(std::ostream& out, const Channel& ch) {
    return out << ch.toString(true);
}
