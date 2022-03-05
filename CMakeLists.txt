cmake_minimum_required(VERSION 3.15)
project(BC95XLT_prog)

# load additional detection for asio
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(src)
SET(CPACK_SOURCE_IGNORE_FILES "/build/;/*.swp;.git*")
INCLUDE(InstallRequiredSystemLibraries)
include (CPack)
