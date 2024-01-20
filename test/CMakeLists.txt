add_library(test_setup INTERFACE)
target_compile_definitions(test_setup INTERFACE USE_CATCH2_VERSION=${Catch2_VERSION_MAJOR})
target_link_libraries(test_setup INTERFACE $<IF:$<STREQUAL:"${Catch2_VERSION_MAJOR}","2">,Catch2::Catch2,Catch2::Catch2WithMain>)

set(my_tests BitoptTest ChannelTest RadioTest)

foreach(TEST ${my_tests})
    add_executable(${TEST} ${TEST}.cpp)
    add_test(${TEST} ${TEST})
    target_compile_features(${TEST} PRIVATE cxx_std_20)
    target_include_directories(${TEST} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${TEST} bc95xlt test_setup) 
endforeach(TEST)
