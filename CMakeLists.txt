cmake_minimum_required(VERSION 3.16)
project(raspbell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (RASPBELL_COMPILE_APP)
    add_subdirectory(app)
endif()

if (RASPBELL_COMPILE_HARDWARE)
    add_subdirectory(hardware)
endif()