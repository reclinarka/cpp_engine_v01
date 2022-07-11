cmake_minimum_required(VERSION 3.22)
project(mmtest)

set(CMAKE_CXX_STANDARD 20)
set(EXEC_NAME mmtest)

#set(_SPDLOG_HOME C:/Users/recli/Documents/spdlog/spdlog/)
#set(SPDLOG_DIR ${_SPDLOG_HOME}/cmake/)

set(_SFML_HOME C:/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${_SFML_HOME}/lib/cmake/SFML)

include_directories(${_SFML_HOME}/include)
#include_directories(${_SPDLOG_HOME}/include)
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)

#if(NOT TARGET spdlog)
#    # Stand-alone build
#    find_package(spdlog REQUIRED)
#endif()

add_executable(${EXEC_NAME} main.cpp)
target_link_libraries(${EXEC_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
