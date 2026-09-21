cmake_minimum_required(VERSION 3.16)
project(raspbell LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

add_subdirectory(app)
add_subdirectory(hardware)