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
    CPPUNIT_TEST_SUITE_END();
public:
    void testHumanReadable() {
        for (const auto& pair : tstchannel) {
            Channel a(pair.human, true);
            std::string result{a.toString(true)};
            CPPUNIT_ASSERT(pair.human == result);
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
    { "21,987.6435,R,S,S", "21,987.6435,R,S,S" }, 
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
