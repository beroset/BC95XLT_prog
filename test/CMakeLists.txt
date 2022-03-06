cmake_minimum_required(VERSION 3.15)
include_directories( ${PROJECT_SOURCE_DIR}/src)
add_executable(ChannelTest ChannelTest.cpp)
add_test(ChannelTest ChannelTest)

target_link_libraries(ChannelTest bc95xlt cppunit)
