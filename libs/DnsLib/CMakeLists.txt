cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME
        DnsLib)

set(LIBRARY_NAME
        DnsLib)

set(LIBRARY_HEADERS_DIR
        include)

file(GLOB LIBRARY_HEADERS
        "include/*.h")

set(LIBRARY_SOURCE_DIR
        src)

file(GLOB LIBRARY_SOURCES
        "src/*.cpp")

project(${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC
        ${LIBRARY_HEADERS}
        ${LIBRARY_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

add_subdirectory(test)