#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Channel.h"
#if USE_CATCH2_VERSION == 2
#  define CATCH_CONFIG_MAIN
#  include <catch2/catch.hpp>
#elif USE_CATCH2_VERSION == 3
#  include <catch2/catch_test_macros.hpp>
#else
#  error "Catch2 version unknown"
#endif

TEST_CASE( "Use and read boolean options", "[boolopt]" ) {
    SECTION("Default constructor is 'R'") {
        Boolopt a{};
        Boolopt b{'R'};
        std::stringstream alpha;
        alpha << a;
        std::stringstream beta;
        beta << b;
        REQUIRE(alpha.str() == beta.str());
    }
    SECTION("Default is not 'S'") {
        Boolopt a{};
        Boolopt b{'S'};
        std::stringstream alpha;
        alpha << a;
        std::stringstream beta;
        beta << b;
        REQUIRE(alpha.str() != beta.str());
    }
    SECTION("Construct 'S'") {
        Boolopt a{'S'};
        std::stringstream alpha;
        alpha << a;
        REQUIRE(alpha.str() == "S");
    }
    SECTION("Encode set Boolopt to stream") {
        std::stringstream alpha;
        alpha << "S";
        Boolopt a;
        alpha >> a;
        REQUIRE(alpha.str() == "S");
    }
    SECTION("Encode reset Boolopt to stream") {
        Boolopt a{'R'};
        std::stringstream alpha;
        alpha << a;
        REQUIRE(alpha.str() == "R");
    }
    SECTION("Decode reset Boolopt from stream") {
        std::stringstream alpha;
        alpha << "R";
        Boolopt a;
        alpha >> a;
        REQUIRE(alpha.str() == "R");
    }
}
