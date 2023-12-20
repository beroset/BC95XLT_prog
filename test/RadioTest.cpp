#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Radio.h"
#if USE_CATCH2_VERSION == 2
#  define CATCH_CONFIG_MAIN
#  include <catch2/catch.hpp>
#elif USE_CATCH2_VERSION == 3
#  include <catch2/catch_test_macros.hpp>
#else
#  error "Catch2 version unknown"
#endif

TEST_CASE( "Test ", "[radio]" ) {
    struct ChannelPair {
        std::string_view human;
        std::string_view scanner;
    };
    static std::vector<ChannelPair> tstchannel = {
        { "21,987.6435,R,S,S", "^C21^F987.6435^LR^PS^DS" },
        { "200,27.1234,S,R,S", "^C200^F27.1234^LS^PR^DS" },
        { "2,145.2550,R,R,S", "^C2^F145.2550^LR^PR^DS" },
        { "1,47.1250,R,R,R", "^C1^F47.1250^LR^PR^DR" },
        { "100,164.5251,S,S,S", "^C100^F164.5251^LS^PS^DS" },
    };

    SECTION("Dump radio into human readable form") {
        RadioContents rc{
            "DUMMY",
            "V1.0"
        };
            
        for (const auto& pair : tstchannel) {
            rc.channel_list.emplace_back(pair.human, true);
        }
        std::stringstream line;
        line << rc;
        std::string result{line.str()};

        std::string desired{R"(# model: DUMMY
# version: V1.0
21,987.6435,R,S,S
200,27.1234,S,R,S
2,145.2550,R,R,S
1,47.1250,R,R,R
100,164.5251,S,S,S
)"};

        REQUIRE(result == desired);
    }
}
