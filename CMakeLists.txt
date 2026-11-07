cmake_minimum_required(VERSION 3.16)
project(raspbell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_COMPONENTS Core Quick Widgets HttpServer Sql Multimedia MultimediaWidgets)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

if(RASPBELL_COMPILE_APP)
  add_subdirectory(app)
endif()

if(RASPBELL_COMPILE_HARDWARE)
  add_subdirectory(hardware)
endif()

file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)
