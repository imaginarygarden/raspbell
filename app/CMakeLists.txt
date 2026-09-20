file(APP_SOURCES GLOB_RECURSE CONFIGURE_DEPENDS "src/*.cpp")

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE "src/")