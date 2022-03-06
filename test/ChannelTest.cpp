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
    CPPUNIT_TEST(testDefaultBoolopt);
    CPPUNIT_TEST(testSetBoolopt);
    CPPUNIT_TEST(testSetDecodeBoolopt);
    CPPUNIT_TEST(testSetEncodeBoolopt);
    CPPUNIT_TEST(testResetDecodeBoolopt);
    CPPUNIT_TEST(testResetEncodeBoolopt);
    CPPUNIT_TEST_SUITE_END();
public:
    void testDefaultBoolopt() {
        Boolopt a{};
        Boolopt b{'R'};
        std::stringstream alpha;
        alpha << a;
        std::stringstream beta;
        beta << b;
        std::cout << a << " --> " << b << "\n";
        CPPUNIT_ASSERT(alpha.str() == beta.str());
    }
    void testSetBoolopt() {
        Boolopt a{};
        Boolopt b{'S'};
        std::stringstream alpha;
        alpha << a;
        std::stringstream beta;
        beta << b;
        std::cout << a << " --> " << b << "\n";
        CPPUNIT_ASSERT(alpha.str() != beta.str());
    }
    void testSetDecodeBoolopt() {
        Boolopt a{'S'};
        std::stringstream alpha;
        alpha << a;
        std::cout << a << "\n";
        CPPUNIT_ASSERT(alpha.str() == "S");
    }
    void testSetEncodeBoolopt() {
        std::stringstream alpha;
        alpha << "S";
        Boolopt a;
        alpha >> a;
        std::cout << a << "\n";
        CPPUNIT_ASSERT(alpha.str() == "S");
    }
    void testResetDecodeBoolopt() {
        Boolopt a{'R'};
        std::stringstream alpha;
        alpha << a;
        std::cout << a << "\n";
        CPPUNIT_ASSERT(alpha.str() == "R");
    }
    void testResetEncodeBoolopt() {
        std::stringstream alpha;
        alpha << "R";
        Boolopt a;
        alpha >> a;
        std::cout << a << "\n";
        CPPUNIT_ASSERT(alpha.str() == "R");
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
