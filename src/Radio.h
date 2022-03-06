#ifndef MY_RADIO_H
#define MY_RADIO_H

#include "Channel.h"
#include <string>
#include <vector>

struct RadioContents {
    std::string model;
    std::string version;
    std::vector<Channel> channel_list;
    friend std::ostream& operator<<(std::ostream& out, const RadioContents& radio_contents);
    friend std::istream& operator>>(std::istream& in, RadioContents& radio_contents);
};

// read the programming data from the radio
RadioContents read_radio(const char* portname, bool verbose=false);
// write the programming data to the radio
void write_radio(const char* portname, const RadioContents& radio_data, bool verbose=false);

#endif // MY_RADIO_H
