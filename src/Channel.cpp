#include "Channel.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

Channel::Channel(std::string_view line) {
    std::stringstream buffer(std::string{line});
    bool valid{false};
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
                lockout = chunk.front() == 'S';
                break;
            case 'P':
                priority = chunk.front() == 'S';
                break;
            case 'D':
                delay = chunk.front() == 'S';
                valid = true;
                break;
            default:
                // probably the first part of the line -- ignore it
                ;
        }
    }
    if (!valid) {
        throw std::runtime_error("Error reading channel");
    }
}

std::ostream& operator<<(std::ostream& out, const Channel& ch) {
    return out << ch.toString(true);
}

std::string Channel::toString(bool human_readable) const {
    static std::string_view sr{"RS"};
    std::stringstream ss;
    ss << (human_readable ? "" : "^C") << static_cast<int>(number)
                << (human_readable ? "," : "^F") << std::fixed << std::setprecision(4) << frequency
                << (human_readable ? "," : "^L") << sr[lockout]
                << (human_readable ? "," : "^P") << sr[priority]
                << (human_readable ? "," : "^D") << sr[delay]
                ;
    return ss.str();
}
