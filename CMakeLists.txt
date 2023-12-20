cmake_minimum_required(VERSION 3.20)
project(BC95XLT_prog VERSION 1.0.0)

# options off-by-default that you can enable
option(WITH_TEST "Build the test suite" OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
# load additional detection for asio
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
endif()

add_subdirectory(src)

if (WITH_TEST)
    find_package(Catch2 REQUIRED)
    enable_testing()
    add_subdirectory(test)
endif() 

SET(CPACK_SOURCE_IGNORE_FILES "/build/;/*.swp;.git*")
INCLUDE(InstallRequiredSystemLibraries)
include (CPack)
