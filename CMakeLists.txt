cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME DNS)
set(EXECUTABLE_NAME DNS)

set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARIES_DIR libs)
set(LIBRARIES DnsLib)

project(${PROJECT_NAME})

#########
# GTest #
#########
enable_testing()

###########
# Project #
###########
add_executable(${EXECUTABLE_NAME} ${SOURCE})

foreach (LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach (LIBRARY)
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARIES})
