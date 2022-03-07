set(EXECUTABLE_NAME "BC95XLT_prog")
find_package(Asio REQUIRED)

add_library(bc95xlt STATIC Channel.cpp Radio.cpp)
target_include_directories(bc95xlt PRIVATE ${ASIO_INCLUDE_DIR})
target_compile_definitions(bc95xlt PRIVATE ASIO_STANDALONE)
if(WIN32)
    target_link_libraries(bc95xlt PRIVATE ws2_32)
endif()

add_executable(${EXECUTABLE_NAME} main.cpp) 
target_link_libraries(${EXECUTABLE_NAME} bc95xlt)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
