cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

set(TEST_PROJECT_NAME
        DnsLibTests
        )

file(GLOB LIBRARY_TESTS_SOURCE *.cpp)
project(${TEST_PROJECT_NAME})

enable_testing()

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})
target_link_libraries(${TEST_PROJECT_NAME}
        gtest
        gtest_main
        ${LIBRARY_NAME} # NOTE: This is defined from project above
        )

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})
