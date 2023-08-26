cmake_minimum_required(VERSION 3.15)
include_directories( ${PROJECT_SOURCE_DIR}/src)

add_executable(BitoptTest BitoptTest.cpp)
add_test(BitoptTest BitoptTest)
target_link_libraries(BitoptTest bc95xlt cppunit)

add_executable(ChannelTest ChannelTest.cpp)
add_test(ChannelTest ChannelTest)
target_link_libraries(ChannelTest bc95xlt cppunit)

add_test(RadioTest RadioTest)
add_executable(RadioTest RadioTest.cpp)
target_link_libraries(RadioTest bc95xlt cppunit)
