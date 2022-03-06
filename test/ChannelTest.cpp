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
    CPPUNIT_TEST(testBoolopt);
    CPPUNIT_TEST_SUITE_END();
public:
    void testBoolopt() {
        Boolopt a{};
        Boolopt b{'R'};
        std::stringstream alpha;
        alpha << a;
        std::stringstream beta;
        beta << b;
        std::cout << a << " --> " << b << "\n";
        CPPUNIT_ASSERT(alpha.str() == beta.str());
    }

private:
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
