#ifndef MY_CHANNEL_H
#define MY_CHANNEL_H
#include <iostream>
#include <string>
#include <string_view>

struct Boolopt {
    bool on;
    Boolopt(char ch = 'R');
    friend std::ostream& operator<<(std::ostream& out, const Boolopt& boolopt);
    friend std::istream& operator>>(std::istream& in, Boolopt boolopt);
};

struct Channel {
    uint8_t number;
    float frequency;
    Boolopt lockout;
    Boolopt priority;
    Boolopt delay;
    Channel(std::string_view line, bool human_readable = false);
    std::string toString(bool human_readable = false) const;
    friend std::ostream& operator<<(std::ostream& out, const Channel& ch);
};
#endif // MY_CHANNEL_H
