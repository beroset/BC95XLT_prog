#ifndef MY_CHANNEL_H
#define MY_CHANNEL_H
#include <iostream>
#include <string>
#include <string_view>

struct Channel {
    uint8_t number;
    float frequency;
    bool lockout;
    bool priority;
    bool delay;
    Channel(std::string_view line);
    std::string toString(bool human_readable = false) const;
    friend std::ostream& operator<<(std::ostream& out, const Channel& ch);
};
#endif // MY_CHANNEL_H
