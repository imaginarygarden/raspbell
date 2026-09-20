file(HARDWARE_SOURCES GLOB_RECURSE CONFIGURE_DEPENDS "src/*.cpp")

add_executable(hardware ${HARDWARE_SOURCES})

target_include_directories(hardware PRIVATE "src/")