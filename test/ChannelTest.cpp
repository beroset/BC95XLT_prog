#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include "Channel.h"

class ChannelTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ChannelTest);
    CPPUNIT_TEST(testHumanReadable);
    CPPUNIT_TEST(testHumanToScannerTranslate);
    CPPUNIT_TEST(testScannerReadable);
    CPPUNIT_TEST(testScannerToHumanTranslate);
    CPPUNIT_TEST_SUITE_END();
public:
    void testHumanReadable() {
        for (const auto& pair : tstchannel) {
            Channel a(pair.human, true);
            std::string result{a.toString(true)};
            std::cout << pair.human << " => "  << result << "\n";
            CPPUNIT_ASSERT(pair.human == result);
        }
    }
    void testHumanToScannerTranslate() {
        for (const auto& pair : tstchannel) {
            Channel a(pair.human, true);
            std::string result{a.toString(false)};
            std::cout << pair.human << " => "  << result << "\n";
            CPPUNIT_ASSERT(pair.scanner == result);
        }
    }
    void testScannerReadable() {
        for (const auto& pair : tstchannel) {
            std::stringstream line;
            line << "RCM" << pair.scanner << '\r';
            Channel a(line.str(), false);
            std::string result{a.toString(true)};
            std::cout << pair.human << " => "  << result << "\n";
            CPPUNIT_ASSERT(pair.human == result);
        }
    }
    void testScannerToHumanTranslate() {
        for (const auto& pair : tstchannel) {
            std::stringstream line;
            line << "RCM" << pair.scanner << '\r';
            Channel a(line.str(), false);
            std::string result{a.toString(false)};
            std::cout << pair.scanner << " => "  << result << "\n";
            CPPUNIT_ASSERT(pair.scanner == result);
        }
    }

private:
    struct ChannelPair {
        std::string_view human;
        std::string_view scanner;
    };
    static std::vector<ChannelPair> tstchannel;
};

std::vector<ChannelTest::ChannelPair> ChannelTest::tstchannel{
    { "21,987.6435,R,S,S", "^C21^F987.6435^LR^PS^DS" },
    { "200,27.1234,S,R,S", "^C200^F27.1234^LS^PR^DS" },
    { "2,145.2550,R,R,S", "^C2^F145.2550^LR^PR^DS" },
    { "1,47.1250,R,R,R", "^C1^F47.1250^LR^PR^DR" },
    { "100,164.5251,S,S,S", "^C100^F164.5251^LS^PS^DS" },
};

CPPUNIT_TEST_SUITE_REGISTRATION(ChannelTest);

int main()
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  bool wasSuccessful = runner.run();
  std::cout << "wasSuccessful = " << std::boolalpha << wasSuccessful << '\n';
  return !wasSuccessful;
}
