project(keditor)

cmake_minimum_required(VERSION 3.7)
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
add_executable(keditor
    src/main.cpp
    src/list.cpp
    src/line.cpp
    src/activezone.cpp
    src/terminal.cpp
)