file(GLOB_RECURSE HARDWARE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(hardware ${HARDWARE_SOURCES})

target_include_directories(hardware PRIVATE "src/")