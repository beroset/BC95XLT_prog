cmake_minimum_required(VERSION 3.15)
include_directories( ${PROJECT_SOURCE_DIR}/src)
add_executable(BitoptTest BitoptTest.cpp)
add_executable(ChannelTest ChannelTest.cpp)
add_test(BitoptTest BitoptTest)
add_test(ChannelTest ChannelTest)

target_link_libraries(BitoptTest bc95xlt cppunit)
target_link_libraries(ChannelTest bc95xlt cppunit)
